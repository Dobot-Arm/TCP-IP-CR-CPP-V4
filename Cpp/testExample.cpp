

#include "api/Dashboard.h"
#include "api/Feedback.h"
#include "api/ErrorInfoBean.h"
#include "api/ErrorInfoHelper.h"
#include <iostream>
#include <algorithm>
#include <regex>
#include <mutex>
#include <fstream>

class DobotTcpDemo
{
public:
    DobotTcpDemo();
    ~DobotTcpDemo();
    void moveRobot();

private:
    Dobot::CDashboard m_Dashboard;
};

DobotTcpDemo::DobotTcpDemo()
{
    std::string robotIp = "192.168.5.1";
    unsigned int controlPort = 29999;

    m_Dashboard.Connect(robotIp, controlPort);
}

DobotTcpDemo::~DobotTcpDemo()
{
    m_Dashboard.Disconnect();
}

void DobotTcpDemo::moveRobot()
{
    m_Dashboard.ClearError();
    m_Dashboard.PowerOn();
    m_Dashboard.EnableRobot();
    m_Dashboard.SpeedFactor(1);
    m_Dashboard.DO(1, 1, 1);
    m_Dashboard.GetErrorID();
    m_Dashboard.User(1);
    m_Dashboard.Tool(1);
    m_Dashboard.RobotMode();
    m_Dashboard.SetPayload(1);
    m_Dashboard.ToolDOInstant(1, 1);
    m_Dashboard.AOInstant(1, 1);
    m_Dashboard.VelJ(1);
    m_Dashboard.VelL(1);
    m_Dashboard.RunScript("1");
    m_Dashboard.Stop();
    m_Dashboard.Pause();
    m_Dashboard.Continue();
    m_Dashboard.DisableRobot();
    m_Dashboard.EmergencyStop(1);

    m_Dashboard.PayLoad(1, 1);
    m_Dashboard.DOInstant(1, 1);
    m_Dashboard.ToolDO(1, 1);
    m_Dashboard.AO(1, 1);
    m_Dashboard.AccJ(1);
    m_Dashboard.AccL(1);
    m_Dashboard.CP(1);

    m_Dashboard.SetArmOrientation(1);
    m_Dashboard.SetArmOrientation(1, 1, 1, 1);
    // m_Dashboard.PositiveKin( CDescartesPoint& pt, int User, int Tool);
    // m_Dashboard.InverseKin( CDescartesPoint& pt, int User, int Tool);
    m_Dashboard.SetCollisionLevel(1);
    m_Dashboard.GetAngle();
    m_Dashboard.GetPose();
    m_Dashboard.GetPose(1, 1);
    m_Dashboard.ModbusRTUCreate(1, 1);
    m_Dashboard.ModbusRTUCreate(1, 1, "Args... args", 0);

    m_Dashboard.ModbusCreate("aa", 111, 1);
    m_Dashboard.ModbusCreate("11", 11, 1, 1);    //  重载可选参数

    m_Dashboard.ModbusClose(1);
    m_Dashboard.GetInBits(1, 1, 1);

    m_Dashboard.GetInRegs(1, 1, 1);
    m_Dashboard.GetInRegs(1, 1, 1, "aa");    //  重载可选参数

    m_Dashboard.GetCoils(1, 1, 1);
    m_Dashboard.SetCoils(1, 1, 1, "aa");
    m_Dashboard.GetHoldRegs(1, 1, 1);
    m_Dashboard.GetHoldRegs(1, 1, 1, "m_Dashboard.valType");    //  重载可选参数
    m_Dashboard.SetHoldRegs(1, 1, 1, "m_Dashboard.valTab");
    m_Dashboard.SetHoldRegs(1, 1, 1, "m_Dashboard.valTab", " m_Dashboard.valType");    //  重载可选参数
    m_Dashboard.DI(1);
    m_Dashboard.ToolDI(1);
    m_Dashboard.AI(1);
    m_Dashboard.ToolAI(1);
    m_Dashboard.DIGroup(1, 1);

    m_Dashboard.DIGroup("Args... args", 0);

    m_Dashboard.DOGroup(1, 1);
    m_Dashboard.DOGroup("Args... args", 0);
    m_Dashboard.BrakeControl(1, 1);
    m_Dashboard.StartDrag();
    m_Dashboard.StopDrag();
    m_Dashboard.DragSensivity(1, 1);
    m_Dashboard.GetDO(1);
    m_Dashboard.GetAO(1);

    m_Dashboard.GetDOGroup("Args... args", 0);

    m_Dashboard.SetTool485(1);

    m_Dashboard.SetTool485(1, "Args... args", 0);

    m_Dashboard.SetSafeWallEnable(1, 1);
    m_Dashboard.SetToolPower(1);

    m_Dashboard.SetToolMode(1);
    m_Dashboard.SetToolMode(1, " Args... args", 0);

    m_Dashboard.SetBackDistance(1);
    m_Dashboard.SetPostCollisionMode(1);

    m_Dashboard.SetUser(1, "m_Dashboard.value");
    m_Dashboard.SetTool(1, "m_Dashboard.value");
    m_Dashboard.CalcUser(1, 1, "m_Dashboard.offset");
    m_Dashboard.CalcTool(1, 1, "m_Dashboard.offset");
    m_Dashboard.GetInputBool(1);
    m_Dashboard.GetInputInt(1);
    m_Dashboard.GetInputFloat(1);
    m_Dashboard.GetOutputBool(1);
    m_Dashboard.GetOutputInt(1);
    m_Dashboard.GetOutputFloat(1);
    m_Dashboard.SetOutputBool(1, 1);
    m_Dashboard.SetOutputInt(1, 1);
    m_Dashboard.SetOutputFloat(1, 1);
    Dobot::CDescartesPoint pt;
    pt.x = 1;
    pt.y = 1;
    pt.z = 1;
    pt.rx = 1;
    pt.ry = 1;
    pt.rz = 1;

    Dobot::CJointPoint cp;
    cp.j1 = 2;
    cp.j2 = 2;
    cp.j3 = 2;
    cp.j4 = 2;
    cp.j5 = 2;
    cp.j6 = 2;

    Dobot::ModeDistanceIndexStatus mdis;
    mdis.Mode = 3;
    mdis.Distance = 3;
    mdis.Index = 3;
    mdis.Status = 3;

    std::string username = "User=1";
    std::string toolname = "Tool=1";
    // m_Dashboard.MovJ(pt);

    // m_Dashboard.MovJ(pt, username, toolname);

    // m_Dashboard.MovJ(cp);

    // m_Dashboard.MovJ(cp, username, toolname);

    // /// 直线运动，目标点位为笛卡尔点位
    // /// <param name="pt">笛卡尔点位</param>
    // /// <returns>返回执行结果的描述信息</returns>
    // m_Dashboard.MovL(pt);

    // m_Dashboard.MovL(pt, username, toolname);

    // m_Dashboard.MovL(cp);

    // m_Dashboard.MovL(cp, username, toolname);

    // m_Dashboard.MovLIO(pt, mdis);

    // m_Dashboard.MovLIO(pt, mdis, username, toolname);

    // m_Dashboard.MovLIO(cp, mdis);

    // m_Dashboard.MovLIO(cp, mdis, username, toolname);

    // m_Dashboard.MovJIO(pt, mdis);

    // m_Dashboard.MovJIO(pt, mdis, username, toolname);

    // m_Dashboard.MovJIO(cp, mdis);

    // m_Dashboard.MovJIO(cp, mdis, username, toolname);

    // m_Dashboard.Arc(pt, pt);

    // m_Dashboard.Arc(pt, pt, username, toolname);

    // m_Dashboard.Arc(cp, cp);

    // m_Dashboard.Arc(cp, cp, username, toolname);

    // m_Dashboard.Circle(pt, pt, 1);

    // m_Dashboard.Circle(pt, pt, 1, username, toolname);

    // m_Dashboard.Circle(cp, cp, 1);

    // m_Dashboard.Circle(cp, cp, 1, username, toolname);

    m_Dashboard.MoveJog("m_Dashboard.traceName");
    m_Dashboard.MoveJog("m_Dashboard.traceName", username, toolname);

    m_Dashboard.StopMoveJog();

    m_Dashboard.StartPath("m_Dashboard.traceName");

    m_Dashboard.StartPath("m_Dashboard.traceName", username, toolname);

    m_Dashboard.GetStartPose("m_Dashboard.traceName");
    m_Dashboard.RelMovJTool(pt);

    m_Dashboard.RelMovJTool(pt, username, toolname);

    m_Dashboard.RelMovLTool(pt);

    m_Dashboard.RelMovLTool(pt, username, toolname);

    m_Dashboard.RelMovJUser(pt);

    m_Dashboard.RelMovJUser(pt, username, toolname);

    m_Dashboard.RelMovLUser(pt);

    m_Dashboard.RelMovLUser(pt, username, toolname);

    m_Dashboard.RelJointMovJ(cp);

    m_Dashboard.RelJointMovJ(cp, username, toolname);

    m_Dashboard.GetCurrentCommandId();
    m_Dashboard.EnableSafeSkin(1);
    m_Dashboard.SetSafeSkin(1, 1);

    m_Dashboard.ServoJ(cp);

    m_Dashboard.ServoJ(cp, username, toolname);

    m_Dashboard.ServoP(pt);

    m_Dashboard.ServoP(pt, username, toolname);
};

int main()
{
    DobotTcpDemo* demo = new DobotTcpDemo();
    demo->moveRobot();
}
