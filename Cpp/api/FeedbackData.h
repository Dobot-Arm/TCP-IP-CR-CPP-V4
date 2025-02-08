#pragma once
#include <cstdint>

namespace Dobot
{
class CFeedbackData
{
public:
    unsigned short MessageSize = 0;    // 消息字节总长度

    short Reserved1[3];    // 保留位

    long DigitalInputs = 0;     // 数字输入
    long DigitalOutputs = 0;    // 数字输出
    long RobotMode = 0;         // 机器人模式,9标识有错误
    long TimeStamp = 0;         // 时间戳（单位ms）
    long RunTime = 0;         // 机器人开机运行时间（单位ms） 
    long TestValue = 0;      // 内存结构测试标准值  0x0123 4567 89AB CDEF

    
    unsigned char Reserved2[8];    // 保留位

    double SpeedScaling = 0;          // 速度比例

    unsigned char Reserved3[16];    // 保留位

    double VRobot = 0;                // 机器人电压
    double IRobot = 0;                // 机器人电流
    double ProgramState = 0;          // 脚本运行状态
    char SafetyOIn[2];                // 安全IO输入状态
    char SafetyOOut[2];               // 安全IO输出状态

    unsigned char Reserved4[76];    // 保留位

    double QTarget[6];              // 目标关节位置
    double QdTarget[6];             // 目标关节速度
    double QddTarget[6];            // 目标关节加速度
    double ITarget[6];              // 目标关节电流
    double MTarget[6];              // 目标关节扭矩
    double QActual[6];              // 实际关节位置
    double QDActual[6];             // 实际关节速度
    double IActual[6];              // 实际关节电流

    double ActualTCPForce[6];       // TCP各轴受力值（通过六维力原始数据计算）
    double ToolVectorActual[6];     // TCP笛卡尔实际坐标值
    double ToolSpeedActual[6];     // TCP笛卡尔实际速度值
    double TCPForce[6];             // TCP力值
    double ToolVectorTarget[6];     // TCP笛卡尔目标坐标值
    double TCPSpeedTarget[6];       // TCP笛卡尔目标速度值
    double MotorTempetatures[6];    // 关节温度
    double JointModes[6];           // 关节控制模式
    double VActual[6];              // 关节电压

    unsigned char Handtype[4];                 // 手系
    unsigned char User = 0;                    // 用户坐标
    unsigned char Tool = 0;                    // 工具坐标
    unsigned char RunQueuedCmd = 0;            // 算法队列运行标志
    unsigned char PauseCmdFlag = 0;            // 算法队列暂停标志
    unsigned char VelocityRatio = 0;           // 关节速度比例(0~100)
    unsigned char AccelerationRatio = 0;       // 关节加速度比例(0~100)
    unsigned char Reserved5 = 0;               // 保留位
    unsigned char XYZVelocityRatio = 0;        // 笛卡尔位置速度比例(0~100)
    unsigned char RVelocityRatio = 0;          // 笛卡尔姿态速度比例(0~100)
    unsigned char XYZAccelerationRatio = 0;    // 笛卡尔位置加速度比例(0~100)
    unsigned char RAccelerationRatio = 0;      // 笛卡尔姿态加速度比例(0~100)

    unsigned char Reserved6[2];                // 保留位

    unsigned char BrakeStatus = 0;             // 机器人抱闸状态
    unsigned char EnableStatus = 0;            // 机器人使能状态
    unsigned char DragStatus = 0;              // 机器人拖拽状态
    unsigned char RunningStatus = 0;           // 机器人运行状态
    unsigned char ErrorStatus = 0;             // 机器人报警状态
    unsigned char JogStatusCR = 0;               // 机器人点动状态
    unsigned char CRRobotType = 0;               // 机器人型号
    unsigned char DragButtonSignal = 0;        // 按钮板拖拽信号
    unsigned char EnableButtonSignal = 0;      // 按钮板使能信号
    unsigned char RecordButtonSignal = 0;      // 按钮板录制信号
    unsigned char ReappearButtonSignal = 0;    // 按钮板复现信号
    unsigned char JawButtonSignal = 0;         // 按钮板夹爪控制信号
    unsigned char SixForceOnline = 0;          // 六维力在线状态
    unsigned char CollisionStatus =  0;        // 碰撞状态
    unsigned char ArmApproachSatus = 0;        // 小臂安全皮肤接近急停
    unsigned char J4ApproachSatus = 0;         // J4安全皮肤接近急停
    unsigned char J5ApproachSatus = 0;         // J5安全皮肤接近急停
    unsigned char J6ApproachSatus = 0;         // J6安全皮肤接近急停

    unsigned char Reserved7[61];    // 保留位

    double VibrationDisZ = 0;      // 加速度计测量Z轴抖动位移
    long CurrentCommandId = 0;     // 当前运动队列id
    double MActual[6];             // 六个关节实际扭矩
    double Load = 0;               // 负载重量kg
    double CenterX = 0;            // X方向偏心距离mm
    double CenterY = 0;            // Y方向偏心距离mm
    double CenterZ = 0;            // Z方向偏心距离mm
    double UserValue[6];            // 用户坐标值
    double ToolValue[6];               // 工具坐标值

    unsigned char Reserved8[8];    // 保留位

    double SixForceValue[6];       // 当前六维力数据原始值
    double TargetQuaternion[4];    //[qw,qx,qy,qz] 目标四元数
    double ActualQuaternion[4];    //[qw,qx,qy,qz]  实际四元数
    short AutoManualMode = 0;       // 自动/手动模式
    unsigned short ExportStatus = 0;         // U盘导出状态
    char SafetyState =0;                
    /* 安全状态1420 安全状态
        1420:0 急停状态（低有效）
        1420:1 防护性停止状态（低有效）
        1420:2 缩减模式状态（低有效）
        1420:3 非停止状态（低有效）
        1420:4 运动中状态（低有效）
        1420:5 系统急停状态（低有效）
        1420:6 用户急停状态（低有效）
        1420:7 安全原点输出状态（低有效，不在安全原点时有效）
    */
    char SafetyState_Resevered =0;  // 安全状态保留位
    unsigned char Reserved9[18];    // 保留位
};
}    // namespace Dobot
