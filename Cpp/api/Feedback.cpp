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

    // 消息总长度
    m_feedbackData.MessageSize = CBitConverter::ToUShort(pBuffer + iStartIndex);
    iStartIndex += 2;

    //保留位 Reserved1[3]
    int iArrLength = sizeof(m_feedbackData.Reserved1) / sizeof(m_feedbackData.Reserved1[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.Reserved1[i] = CBitConverter::ToShort(pBuffer + iStartIndex);
        iStartIndex += 2;
    }

    m_feedbackData.DigitalInputs  = CBitConverter::ToInt64(pBuffer + iStartIndex);  iStartIndex += 8;
    m_feedbackData.DigitalOutputs = CBitConverter::ToInt64(pBuffer + iStartIndex);  iStartIndex += 8;
    m_feedbackData.RobotMode      = CBitConverter::ToInt64(pBuffer + iStartIndex);  iStartIndex += 8;
    m_feedbackData.TimeStamp      = CBitConverter::ToInt64(pBuffer + iStartIndex);  iStartIndex += 8;
    m_feedbackData.RunTime        = CBitConverter::ToInt64(pBuffer + iStartIndex);  iStartIndex += 8; // 新增字段
    m_feedbackData.TestValue      = CBitConverter::ToInt64(pBuffer + iStartIndex);  iStartIndex += 8;

    // 保留位 Reserved2[8]
    iArrLength = sizeof(m_feedbackData.Reserved2) / sizeof(m_feedbackData.Reserved2[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.Reserved2[i] = pBuffer[iStartIndex];
        iStartIndex += 1;
    }

    // 5. 速度比例和保留位
    m_feedbackData.SpeedScaling = CBitConverter::ToDouble(pBuffer + iStartIndex);  iStartIndex += 8;

    // 保留位 Reserved3[16]
    iArrLength = sizeof(m_feedbackData.Reserved3) / sizeof(m_feedbackData.Reserved3[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.Reserved3[i] = pBuffer[iStartIndex];
        iStartIndex += 1;
    }

    // 电压/电流和程序状态
    m_feedbackData.VRobot       = CBitConverter::ToDouble(pBuffer + iStartIndex);  iStartIndex += 8;
    m_feedbackData.IRobot       = CBitConverter::ToDouble(pBuffer + iStartIndex);  iStartIndex += 8;
    m_feedbackData.ProgramState = CBitConverter::ToDouble(pBuffer + iStartIndex);  iStartIndex += 8; // 新增字段

    // 安全IO状态
    iArrLength = sizeof(m_feedbackData.SafetyOIn) / sizeof(m_feedbackData.SafetyOIn[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.SafetyOIn[i] = pBuffer[iStartIndex];
        iStartIndex += 1;
    }
    iArrLength = sizeof(m_feedbackData.SafetyOOut) / sizeof(m_feedbackData.SafetyOOut[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.SafetyOOut[i] = pBuffer[iStartIndex];
        iStartIndex += 1;
    }

    // 保留位 Reserved4[76]
    iArrLength = sizeof(m_feedbackData.Reserved4) / sizeof(m_feedbackData.Reserved4[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.Reserved4[i] = pBuffer[iStartIndex];
        iStartIndex += 1;
    }

    // 关节目标值（位置/速度/电流等）
    iArrLength = sizeof(m_feedbackData.QTarget)/sizeof(m_feedbackData.QTarget[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.QTarget[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }
    
    iArrLength = sizeof(m_feedbackData.QdTarget)/sizeof(m_feedbackData.QdTarget[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.QdTarget[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    iArrLength = sizeof(m_feedbackData.QddTarget)/sizeof(m_feedbackData.QddTarget[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.QddTarget[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    iArrLength = sizeof(m_feedbackData.ITarget)/sizeof(m_feedbackData.ITarget[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.ITarget[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    iArrLength = sizeof(m_feedbackData.MTarget)/sizeof(m_feedbackData.MTarget[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.MTarget[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    // 实际关节值
    iArrLength = sizeof(m_feedbackData.QActual)/sizeof(m_feedbackData.QActual[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.QActual[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    iArrLength = sizeof(m_feedbackData.QDActual)/sizeof(m_feedbackData.QDActual[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.QDActual[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    iArrLength = sizeof(m_feedbackData.IActual)/sizeof(m_feedbackData.IActual[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.IActual[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    // 工具数据
    iArrLength = sizeof(m_feedbackData.ActualTCPForce)/sizeof(m_feedbackData.ActualTCPForce[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.ActualTCPForce[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    iArrLength = sizeof(m_feedbackData.ToolVectorActual)/sizeof(m_feedbackData.ToolVectorActual[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.ToolVectorActual[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    iArrLength = sizeof(m_feedbackData.ToolSpeedActual)/sizeof(m_feedbackData.ToolSpeedActual[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.ToolSpeedActual[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    iArrLength = sizeof(m_feedbackData.TCPForce)/sizeof(m_feedbackData.TCPForce[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.TCPForce[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    iArrLength = sizeof(m_feedbackData.ToolVectorTarget)/sizeof(m_feedbackData.ToolVectorTarget[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.ToolVectorTarget[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    iArrLength = sizeof(m_feedbackData.TCPSpeedTarget)/sizeof(m_feedbackData.TCPSpeedTarget[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.TCPSpeedTarget[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    // 温度/模式/电压
    iArrLength = sizeof(m_feedbackData.MotorTempetatures)/sizeof(m_feedbackData.MotorTempetatures[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.MotorTempetatures[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    iArrLength = sizeof(m_feedbackData.JointModes)/sizeof(m_feedbackData.JointModes[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.JointModes[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    iArrLength = sizeof(m_feedbackData.VActual)/sizeof(m_feedbackData.VActual[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.VActual[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    // 手系和状态标志
    iArrLength = sizeof(m_feedbackData.Handtype)/sizeof(m_feedbackData.Handtype[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.Handtype[i] = pBuffer[iStartIndex];
        iStartIndex +=1;
    }

    m_feedbackData.User = pBuffer[iStartIndex++];
    m_feedbackData.Tool = pBuffer[iStartIndex++];
    m_feedbackData.RunQueuedCmd = pBuffer[iStartIndex++];
    m_feedbackData.PauseCmdFlag = pBuffer[iStartIndex++];
    m_feedbackData.VelocityRatio = pBuffer[iStartIndex++];
    m_feedbackData.AccelerationRatio = pBuffer[iStartIndex++];
    m_feedbackData.Reserved5 = pBuffer[iStartIndex++];
    m_feedbackData.XYZVelocityRatio = pBuffer[iStartIndex++];
    m_feedbackData.RVelocityRatio = pBuffer[iStartIndex++];
    m_feedbackData.XYZAccelerationRatio = pBuffer[iStartIndex++];
    m_feedbackData.RAccelerationRatio = pBuffer[iStartIndex++];

    // 保留位 Reserved6[2]
    iArrLength = sizeof(m_feedbackData.Reserved6) / sizeof(m_feedbackData.Reserved6[0]);
    for (int i = 0; i < iArrLength; ++i) {
        m_feedbackData.Reserved6[i] = pBuffer[iStartIndex];
        iStartIndex += 1;
    }

    // 状态标志
    m_feedbackData.BrakeStatus = pBuffer[iStartIndex++];
    m_feedbackData.EnableStatus = pBuffer[iStartIndex++];
    m_feedbackData.DragStatus = pBuffer[iStartIndex++];
    m_feedbackData.RunningStatus = pBuffer[iStartIndex++];
    m_feedbackData.ErrorStatus = pBuffer[iStartIndex++];
    m_feedbackData.JogStatusCR = pBuffer[iStartIndex++];
    m_feedbackData.CRRobotType = pBuffer[iStartIndex++];
    m_feedbackData.DragButtonSignal = pBuffer[iStartIndex++];
    m_feedbackData.EnableButtonSignal = pBuffer[iStartIndex++];
    m_feedbackData.RecordButtonSignal = pBuffer[iStartIndex++];
    m_feedbackData.ReappearButtonSignal = pBuffer[iStartIndex++];
    m_feedbackData.JawButtonSignal = pBuffer[iStartIndex++];
    m_feedbackData.SixForceOnline = pBuffer[iStartIndex++];
    m_feedbackData.CollisionStatus = pBuffer[iStartIndex++];
    m_feedbackData.ArmApproachSatus = pBuffer[iStartIndex++];
    m_feedbackData.J4ApproachSatus = pBuffer[iStartIndex++];
    m_feedbackData.J5ApproachSatus = pBuffer[iStartIndex++];
    m_feedbackData.J6ApproachSatus = pBuffer[iStartIndex++];

    // 保留位 Reserved7[61]
    iArrLength = sizeof(m_feedbackData.Reserved7)/sizeof(m_feedbackData.Reserved7[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.Reserved7[i] = pBuffer[iStartIndex];
        iStartIndex +=1;
    }

    // 振动/指令ID/力矩
    m_feedbackData.VibrationDisZ = CBitConverter::ToDouble(pBuffer + iStartIndex); iStartIndex +=8;
    m_feedbackData.CurrentCommandId = CBitConverter::ToInt64(pBuffer + iStartIndex); iStartIndex +=8;

    iArrLength = sizeof(m_feedbackData.MActual)/sizeof(m_feedbackData.MActual[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.MActual[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    //负载参数
    m_feedbackData.Load = CBitConverter::ToDouble(pBuffer + iStartIndex); iStartIndex +=8;
    m_feedbackData.CenterX = CBitConverter::ToDouble(pBuffer + iStartIndex); iStartIndex +=8;
    m_feedbackData.CenterY = CBitConverter::ToDouble(pBuffer + iStartIndex); iStartIndex +=8;
    m_feedbackData.CenterZ = CBitConverter::ToDouble(pBuffer + iStartIndex); iStartIndex +=8;

    //用户坐标/工具坐标
    iArrLength = sizeof(m_feedbackData.UserValue)/sizeof(m_feedbackData.UserValue[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.UserValue[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    iArrLength = sizeof(m_feedbackData.ToolValue)/sizeof(m_feedbackData.ToolValue[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.ToolValue[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    // 保留位
    iArrLength = sizeof(m_feedbackData.Reserved8)/sizeof(m_feedbackData.Reserved8[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.Reserved8[i] = pBuffer[iStartIndex];
        iStartIndex +=1;
    }

    //六维力和四元数
    iArrLength = sizeof(m_feedbackData.SixForceValue)/sizeof(m_feedbackData.SixForceValue[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.SixForceValue[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    iArrLength = sizeof(m_feedbackData.TargetQuaternion)/sizeof(m_feedbackData.TargetQuaternion[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.TargetQuaternion[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    iArrLength = sizeof(m_feedbackData.ActualQuaternion)/sizeof(m_feedbackData.ActualQuaternion[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.ActualQuaternion[i] = CBitConverter::ToDouble(pBuffer + iStartIndex);
        iStartIndex +=8;
    }

    m_feedbackData.AutoManualMode = CBitConverter::ToShort(pBuffer + iStartIndex);iStartIndex=iStartIndex+2;
    m_feedbackData.ExportStatus =CBitConverter::ToShort(pBuffer + iStartIndex);iStartIndex=iStartIndex+2;
    m_feedbackData.SafetyState = pBuffer[iStartIndex++];
    m_feedbackData.SafetyState_Resevered = pBuffer[iStartIndex++];

    // 保留位
    iArrLength = sizeof(m_feedbackData.Reserved9)/sizeof(m_feedbackData.Reserved9[0]);
    for(int i=0; i<iArrLength; ++i){
        m_feedbackData.Reserved9[i] = pBuffer[iStartIndex];
        iStartIndex +=1;
    }

    //std::cout<<(iStartIndex);
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
