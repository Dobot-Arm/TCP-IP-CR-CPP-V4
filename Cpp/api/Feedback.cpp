#include "Feedback.h"

#include <cstdlib>
#include <cstring>

#include "BitConverter.h"
#include <iostream>
namespace Dobot
{
CFeedback::CFeedback()
{
}
CFeedback::~CFeedback()
{
}

void CFeedback::OnConnected()
{
    if (m_thd.joinable()) {
        m_thd.join();
    }
    std::thread thd([this] { OnRecvData(); });
    m_thd.swap(thd);
}

void CFeedback::OnDisconnected()
{
    if (m_thd.joinable()) {
        m_thd.join();
    }
}

const CFeedbackData& CFeedback::GetFeedbackData() const
{
    return m_feedbackData;
}

void CFeedback::OnRecvData()
{
    constexpr int BUFFERSIZE = 4320;    // 1440*3
    char buffer[BUFFERSIZE] = { 0 };
    int iHasRead = 0;
    while (IsConnected()) {
        int iRet = Receive(buffer + iHasRead, BUFFERSIZE - iHasRead);
        if (iRet <= 0) {
            continue;
        }
        iHasRead += iRet;
        if (iHasRead < 1440) {
            continue;
        }

        bool bHasFound = false;    // 是否找到数据包头了
        for (int i = 0; i < iHasRead; ++i) {
            // 找到消息头
            unsigned short iMsgSize = CBitConverter::ToUShort(buffer + i);
            if (1440 != iMsgSize) {
                continue;
            }
            // 校验
            uint64_t checkValue = CBitConverter::ToUInt64(buffer + i + 48);
            if (0x0123456789ABCDEF == checkValue) {    // 找到了校验值
                bHasFound = true;
                if (i != 0) {    // 说明存在粘包，要把前面的数据清理掉
                    iHasRead = iHasRead - i;
                    memmove(buffer, buffer + i, BUFFERSIZE - i);
                }
                break;
            }
        }
        if (!bHasFound) {    // 如果没找到头，判断数据长度是不是快超过了总长度，超过了，说明数据全都有问题，删掉
            if (iHasRead >= BUFFERSIZE)
                iHasRead = 0;
            continue;
        }
        // 再次判断字节数是否够
        if (iHasRead < 1440) {
            continue;
        }
        iHasRead = iHasRead - 1440;
        // 按照协议的格式解析数据
        ParseData(buffer);
        memmove(buffer, buffer + 1440, BUFFERSIZE - 1440);
    }
}

void CFeedback::ParseData(char* pBuffer)
{
    int iStartIndex = 0;

    m_feedbackData.MessageSize = CBitConverter::ToUShort(pBuffer + iStartIndex);
    iStartIndex += 2;

    int iArrLength = sizeof(m_feedbackData.Reserved1) / sizeof(m_feedbackData.Reserved1[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.Reserved1[i] = CBitConverter::ToShort(pBuffer + iStartIndex);
        iStartIndex += 2;
    }

    m_feedbackData.DigitalInputs = CBitConverter::ToInt64(pBuffer + iStartIndex);
    iStartIndex += 8;

    m_feedbackData.DigitalOutputs = CBitConverter::ToInt64(pBuffer + iStartIndex);
    iStartIndex += 8;

    m_feedbackData.RobotMode = CBitConverter::ToInt64(pBuffer + iStartIndex);
    iStartIndex += 8;

    m_feedbackData.TimeStamp = CBitConverter::ToInt64(pBuffer + iStartIndex);
    iStartIndex += 8;

    m_feedbackData.Reserved2 = CBitConverter::ToInt64(pBuffer + iStartIndex);
    iStartIndex += 8;

    m_feedbackData.TestValue = CBitConverter::ToInt64(pBuffer + iStartIndex);
    iStartIndex += 8;

    m_feedbackData.Reserved3 = CBitConverter::ToInt64(pBuffer + iStartIndex);
    iStartIndex += 8;

    m_feedbackData.SpeedScaling = CBitConverter::ToDouble(pBuffer + iStartIndex);
    iStartIndex += 8;

    m_feedbackData.LinearMomentumNorm = CBitConverter::ToDouble(pBuffer + iStartIndex);
    iStartIndex += 8;

    m_feedbackData.VMain = CBitConverter::ToDouble(pBuffer + iStartIndex);
    iStartIndex += 8;

    m_feedbackData.VRobot = CBitConverter::ToDouble(pBuffer + iStartIndex);
    iStartIndex += 8;

    m_feedbackData.IRobot = CBitConverter::ToDouble(pBuffer + iStartIndex);
    iStartIndex += 8;

    m_feedbackData.Reserved4 = CBitConverter::ToDouble(pBuffer + iStartIndex);
    iStartIndex += 8;

    m_feedbackData.Reserved5 = CBitConverter::ToDouble(pBuffer + iStartIndex);
    iStartIndex += 8;

    iArrLength = sizeof(m_feedbackData.ToolAccelerometerValues) / sizeof(m_feedbackData.ToolAccelerometerValues[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.ToolAccelerometerValues[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.ElbowPosition) / sizeof(m_feedbackData.ElbowPosition[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.ElbowPosition[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.ElbowVelocity) / sizeof(m_feedbackData.ElbowVelocity[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.ElbowVelocity[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.QTarget) / sizeof(m_feedbackData.QTarget[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.QTarget[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.QdTarget) / sizeof(m_feedbackData.QdTarget[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.QdTarget[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.QddTarget) / sizeof(m_feedbackData.QddTarget[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.QddTarget[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.ITarget) / sizeof(m_feedbackData.ITarget[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.ITarget[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.MTarget) / sizeof(m_feedbackData.MTarget[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.MTarget[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.QActual) / sizeof(m_feedbackData.QActual[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.QActual[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.QdActual) / sizeof(m_feedbackData.QdActual[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.QdActual[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.IActual) / sizeof(m_feedbackData.IActual[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.IActual[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.IControl) / sizeof(m_feedbackData.IControl[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.IControl[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.ToolVectorActual) / sizeof(m_feedbackData.ToolVectorActual[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.ToolVectorActual[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.TCPSpeedActual) / sizeof(m_feedbackData.TCPSpeedActual[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.TCPSpeedActual[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.TCPForce) / sizeof(m_feedbackData.TCPForce[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.TCPForce[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.ToolVectorTarget) / sizeof(m_feedbackData.ToolVectorTarget[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.ToolVectorTarget[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.TCPSpeedTarget) / sizeof(m_feedbackData.TCPSpeedTarget[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.TCPSpeedTarget[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.MotorTempetatures) / sizeof(m_feedbackData.MotorTempetatures[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.MotorTempetatures[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.JointModes) / sizeof(m_feedbackData.JointModes[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.JointModes[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.VActual) / sizeof(m_feedbackData.VActual[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.VActual[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.Handtype) / sizeof(m_feedbackData.Handtype[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.Handtype[i] = pBuffer[iStartIndex];
        iStartIndex += 1;
    }

    m_feedbackData.User = pBuffer[iStartIndex];
    iStartIndex += 1;

    m_feedbackData.Tool = pBuffer[iStartIndex];
    iStartIndex += 1;

    m_feedbackData.RunQueuedCmd = pBuffer[iStartIndex];
    iStartIndex += 1;

    m_feedbackData.PauseCmdFlag = pBuffer[iStartIndex];
    iStartIndex += 1;

    m_feedbackData.VelocityRatio = pBuffer[iStartIndex];
    iStartIndex += 1;

    m_feedbackData.AccelerationRatio = pBuffer[iStartIndex];
    iStartIndex += 1;

    m_feedbackData.JerkRatio = pBuffer[iStartIndex];
    iStartIndex += 1;

    m_feedbackData.XYZVelocityRatio = pBuffer[iStartIndex];
    iStartIndex += 1;

    m_feedbackData.RVelocityRatio = pBuffer[iStartIndex];
    iStartIndex += 1;

    m_feedbackData.XYZAccelerationRatio = pBuffer[iStartIndex];
    iStartIndex += 1;

    m_feedbackData.RAccelerationRatio = pBuffer[iStartIndex];
    iStartIndex += 1;

    m_feedbackData.XYZJerkRatio = pBuffer[iStartIndex];
    iStartIndex += 1;

    m_feedbackData.RJerkRatio = pBuffer[iStartIndex];
    iStartIndex += 1;

    m_feedbackData.BrakeStatus = pBuffer[iStartIndex];
    iStartIndex += 1;
    m_feedbackData.EnableStatus = pBuffer[iStartIndex];
    iStartIndex += 1;
    m_feedbackData.DragStatus = pBuffer[iStartIndex];
    iStartIndex += 1;
    m_feedbackData.RunningStatus = pBuffer[iStartIndex];
    iStartIndex += 1;
    m_feedbackData.ErrorStatus = pBuffer[iStartIndex];
    iStartIndex += 1;
    m_feedbackData.JogStatus = pBuffer[iStartIndex];
    iStartIndex += 1;
    m_feedbackData.RobotType = pBuffer[iStartIndex];
    iStartIndex += 1;
    m_feedbackData.DragButtonSignal = pBuffer[iStartIndex];
    iStartIndex += 1;
    m_feedbackData.EnableButtonSignal = pBuffer[iStartIndex];
    iStartIndex += 1;
    m_feedbackData.RecordButtonSignal = pBuffer[iStartIndex];
    iStartIndex += 1;
    m_feedbackData.ReappearButtonSignal = pBuffer[iStartIndex];
    iStartIndex += 1;
    m_feedbackData.JawButtonSignal = pBuffer[iStartIndex];
    iStartIndex += 1;
    m_feedbackData.SixForceOnline = pBuffer[iStartIndex];
    iStartIndex += 1;

    iArrLength = sizeof(m_feedbackData.Reserved6) / sizeof(m_feedbackData.Reserved6[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.Reserved6[i] = pBuffer[iStartIndex];
        iStartIndex += 1;
    }

    m_feedbackData.VibrationdisZ = CBitConverter::ToDouble(pBuffer + iStartIndex);
    iStartIndex += 8;

    m_feedbackData.CurrentCommandId = CBitConverter::ToInt64(pBuffer + iStartIndex);
    iStartIndex += 8;

    iArrLength = sizeof(m_feedbackData.MActual) / sizeof(m_feedbackData.MActual[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.MActual[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    m_feedbackData.Load = CBitConverter::ToDouble(pBuffer + iStartIndex);
    iStartIndex += 8;

    m_feedbackData.CenterX = CBitConverter::ToDouble(pBuffer + iStartIndex);
    iStartIndex += 8;

    m_feedbackData.CenterY = CBitConverter::ToDouble(pBuffer + iStartIndex);
    iStartIndex += 8;

    m_feedbackData.CenterZ = CBitConverter::ToDouble(pBuffer + iStartIndex);
    iStartIndex += 8;

    iArrLength = sizeof(m_feedbackData.UserValu) / sizeof(m_feedbackData.UserValu[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.UserValu[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.Tools) / sizeof(m_feedbackData.Tools[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.Tools[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    m_feedbackData.TraceIndex = CBitConverter::ToDouble(pBuffer + iStartIndex);
    iStartIndex += 8;

    iArrLength = sizeof(m_feedbackData.SixForceValue) / sizeof(m_feedbackData.SixForceValue[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.SixForceValue[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.TargetQuaternion) / sizeof(m_feedbackData.TargetQuaternion[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.TargetQuaternion[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.ActualQuaternion) / sizeof(m_feedbackData.ActualQuaternion[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.ActualQuaternion[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex += 8;
    }

    iArrLength = sizeof(m_feedbackData.Reserved7) / sizeof(m_feedbackData.Reserved7[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.Reserved7[i] = pBuffer[iStartIndex];
        iStartIndex += 1;
    }

    m_IsDataHasRead = true;
}

std::string CFeedback::ConvertRobotMode()
{
    switch (m_feedbackData.RobotMode) {
        case -1:
            return "NO_CONTROLLER";
        case 0:
            return "NO_CONNECTED";
        case 1:
            return "ROBOT_MODE_INIT";
        case 2:
            return "ROBOT_MODE_BRAKE_OPEN";
        case 3:
            return "ROBOT_RESERVED";
        case 4:
            return "ROBOT_MODE_DISABLED";
        case 5:
            return "ROBOT_MODE_ENABLE";
        case 6:
            return "ROBOT_MODE_BACKDRIVE";
        case 7:
            return "ROBOT_MODE_RUNNING";
        case 8:
            return "ROBOT_MODE_RECORDING";
        case 9:
            return "ROBOT_MODE_ERROR";
        case 10:
            return "ROBOT_MODE_PAUSE";
        case 11:
            return "ROBOT_MODE_JOG";
    }
    std::string str("UNKNOW：RobotMode={0}");
    str += std::to_string(m_feedbackData.RobotMode);
    return str;
}
}    // namespace Dobot
