
#include "DobotTcpDemo.h"
#include <fstream>

DobotTcpDemo::DobotTcpDemo()
{
    std::string robotIp = "192.168.5.1";
    unsigned int controlPort = 29999;
    unsigned int feekPort = 30004;

    std::cout << "开始连接" << std::endl;
    m_Dashboard.Connect(robotIp, controlPort);
    m_CFeedback.Connect(robotIp, feekPort);
    std::cout << "连接成功" << std::endl;
    m_CErrorInfoHelper.ParseControllerJsonFile("../alarmController.json");
    m_CErrorInfoHelper.ParseServoJsonFile("../alarmServo.json");
    threadGetFeedBackInfo = std::thread(&DobotTcpDemo::getFeedBackInfo, this);
    threadGetFeedBackInfo.detach();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    threadClearRobotError = std::thread(&DobotTcpDemo::clearRobotError, this);
    threadClearRobotError.detach();
}

DobotTcpDemo::~DobotTcpDemo()
{
    m_Dashboard.Disconnect();
    m_CFeedback.Disconnect();
}

void DobotTcpDemo::moveRobot()
{
    double pointa[] = { -90, 20, 0, 0, 0, 0 };
    double pointb[] = { 90, 20, 0, 0, 0, 0 };
    m_Dashboard.EnableRobot();
    Dobot::CJointPoint ptPointa;
    Dobot::CJointPoint ptPointb;
    memcpy(&ptPointa, pointa, sizeof(ptPointa));
    memcpy(&ptPointb, pointb, sizeof(ptPointb));
    int currentCommandID = 0;
    while (true) {
        getCurrentCommandID(m_Dashboard.MovJ(ptPointa), currentCommandID);
        moveArriveFinish(ptPointa, currentCommandID);
        getCurrentCommandID(m_Dashboard.MovJ(ptPointb), currentCommandID);
        moveArriveFinish(ptPointb, currentCommandID);
    }
}

void DobotTcpDemo::getCurrentCommandID(std::string recvData, int& currentCommandID)
{
    std::cout << "recvData " << recvData << std::endl;
    currentCommandID = 2147483647;    // 初始值  int-max
    if (recvData.find("device does not connected") != std::string::npos) {
        std::cout << "device does not connected " << std::endl;
        return;
    }

    if (recvData.find("send error") != std::string::npos) {
        std::cout << "send error" << std::endl;
        return;
    }

    // recvData 为 0,{2},MovJ(joint={-90, 20, 0, 0, 0, 0})     vecRecv为所有数字的集合 [ 0,2,-90, 20, 0, 0, 0, 0]
    std::vector<std::string> vecRecv = regexRecv(recvData);

    // vecRecv[0]为指令是否下发成功   vecRecv[1]为返回运动指令currentCommandID
    if (vecRecv.size() >= 2U && std::stoi(vecRecv[0]) == 0) {
        currentCommandID = std::stoi(vecRecv[1]);
    }
}

void DobotTcpDemo::getFeedBackInfo()
{
    std::cout << "Start GetFeedBackInfo" << std::endl;
    while (true) {
        {
            std::unique_lock<std::mutex> lockValue(m_mutexValue);
            feedbackData = m_CFeedback.GetFeedbackData();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void DobotTcpDemo::moveArriveFinish(const Dobot::CJointPoint& pt, int currentCommandID)
{
    std::cout << "Wait moveArriveFinish" << std::endl;
    while (true) {
        {
            std::unique_lock<std::mutex> lockValue(m_mutexValue);
            if (feedbackData.CurrentCommandId > currentCommandID) {
                break;
            }
            if (feedbackData.CurrentCommandId == currentCommandID && feedbackData.RobotMode == 5) {
                break;
            }
        }

        {
            std::unique_lock<std::mutex> lockValue(m_mutexState);
            if (finishState) {
                finishState = false;
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
};

std::vector<std::string> DobotTcpDemo::regexRecv(std::string getRecvInfo)
{
    std::regex pattern("-?\\d+");
    std::smatch matches;
    std::string::const_iterator searchStart(getRecvInfo.cbegin());
    std::vector<std::string> vecErrorId;
    while (std::regex_search(searchStart, getRecvInfo.cend(), matches, pattern)) {
        for (auto& match : matches) {
            vecErrorId.push_back(match.str());
        }
        searchStart = matches.suffix().first;
    }
    return vecErrorId;
};

void DobotTcpDemo::clearRobotError()
{
    std::cout << "Start CheckRobotError" << std::endl;
    while (true) {
        {
            std::unique_lock<std::mutex> lockValue(m_mutexValue);
            if (feedbackData.ErrorStatus) {
                std::vector<std::string> errorIdVec = regexRecv(m_Dashboard.GetErrorID());
                for (int i = 1; i < errorIdVec.size(); i++) {
                    Dobot::CErrorInfoBean beanController;
                    Dobot::CErrorInfoBean beanServo;
                    if (std::stoi(errorIdVec[i]) != 0) {
                        printf("告警码：%s\n", errorIdVec[i].c_str());
                        if (m_CErrorInfoHelper.FindController(std::stoi(errorIdVec[i]), beanController)) {
                            printf("控制器告警：%d, 告警原因：%s,%s\n", beanController.id,
                                   beanController.zh_CN.description.c_str(), beanController.en.description.c_str());
                        } else {
                            if (m_CErrorInfoHelper.FindServo(std::stoi(errorIdVec[i]), beanServo)) {
                                printf("伺服告警：%d,告警原因：%s, %s\n", beanServo.id,
                                       beanServo.zh_CN.description.c_str(), beanServo.en.description.c_str());
                            }
                        }
                    }
                }
                char choose[50] = { "" };
                std::cout << "输入1, 将清除错误, 机器继续运行:" << std::endl;
                std::cin >> choose;
                std::cout << "您的选择： " << choose << std::endl;
                try {
                    int result = std::stoi(choose);
                    if (result == 1) {
                        std::cout << "清除错误，机器继续运行！" << std::endl;
                        m_Dashboard.ClearError();
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Exception caught: " << e.what() << std::endl;
                } catch (...) {
                    std::cerr << "Unknown exception caught." << std::endl;
                }
            } else {
                if (feedbackData.RobotMode == 11) {
                    std::cout << "机器发生碰撞 " << std::endl;
                    char choose[50] = { "" };
                    std::cout << "输入1, 将清除碰撞, 机器继续运行: " << std::endl;
                    std::cin >> choose;
                    std::cout << "您的选择： " << choose << std::endl;
                    try {
                        int result = std::stoi(choose);
                        if (result == 1) {
                            std::cout << "清除错误，机器继续运行！" << std::endl;
                            m_Dashboard.ClearError();
                        }
                    } catch (const std::exception& e) {
                        std::cerr << "Exception caught: " << e.what() << std::endl;
                    } catch (...) {
                        std::cerr << "Unknown exception caught." << std::endl;
                    }
                }

                if (!feedbackData.EnableStatus) {
                    std::cout << "机器未使能 " << std::endl;
                    char choose[50] = { "" };
                    std::cout << "输入1, 机器将使能: " << std::endl;
                    std::cin >> choose;
                    std::cout << "您的选择： " << choose << std::endl;
                    try {
                        int result = std::stoi(choose);
                        if (result == 1) {
                            std::cout << "机器使能！" << std::endl;
                            m_Dashboard.EnableRobot();
                        }
                    } catch (const std::exception& e) {
                        std::cerr << "Exception caught: " << e.what() << std::endl;
                    } catch (...) {
                        std::cerr << "Unknown exception caught." << std::endl;
                    }
                }

                if (!feedbackData.ErrorStatus && feedbackData.EnableStatus && feedbackData.RobotMode == 5) {
                    std::unique_lock<std::mutex> lockValue(m_mutexState);
                    finishState = true;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
}
