#include "Dashboard.h"
#include <sstream>

namespace Dobot
{
CDashboard::CDashboard()
{
}
CDashboard::~CDashboard()
{
}

void CDashboard::OnConnected()
{
}
void CDashboard::OnDisconnected()
{
}

std::string CDashboard::SendRecvMsg(std::string& str)
{
    std::unique_lock<std::mutex> lockValue(m_mutex);
    if (!IsConnected()) {
        return "device does not connected!!!";
    }
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::SendRecvMsg(char* cmd)
{
    std::unique_lock<std::mutex> lockValue(m_mutex);
    if (!IsConnected()) {
        return "device does not connected!!!";
    }
    if (!SendData(cmd)) {
        strcat(cmd, ":send error");
        return cmd;
    }

    return WaitReply(5000);
}

std::string CDashboard::ClearError()
{
    std::string str = "ClearError()";
    return SendRecvMsg(str);
}

std::string CDashboard::PowerOn()
{
    std::string str = "PowerOn()";

    return SendRecvMsg(str);
}

std::string CDashboard::EmergencyStop(int value)
{
    std::string str = "EmergencyStop(" + std::to_string(value) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::EnableRobot()
{
    std::string str = "EnableRobot()";

    return SendRecvMsg(str);
}

std::string CDashboard::DisableRobot()
{
    std::string str = "DisableRobot()";

    return SendRecvMsg(str);
}

std::string CDashboard::SpeedFactor(int ratio)
{
    std::ostringstream oss;
    oss << "SpeedFactor(" << ratio << ")";
    std::string str = oss.str();

    return SendRecvMsg(str);
}

std::string CDashboard::GetErrorID()
{
    std::string str = "GetErrorID()";

    return SendRecvMsg(str);
}

std::string CDashboard::User(int index)
{
    std::string str = "User(" + std::to_string(index) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::Tool(int index)
{
    std::string str = "Tool(" + std::to_string(index) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::RobotMode()
{
    std::string str = "RobotMode()";

    return SendRecvMsg(str);
};

std::string CDashboard::PayLoad(double weight, double inertia)
{
    std::string str = "PayLoad(" + std::to_string(weight) + "," + std::to_string(inertia) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::DO(int index, int status)
{
    std::string str = "DO(" + std::to_string(index) + "," + std::to_string(status) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::DO(int index, int status, int time)
{
    std::string str = "DO(" + std::to_string(index) + "," + std::to_string(status) + "," + std::to_string(time) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::DOInstant(int index, int status)
{
    std::string str = "DOInstant(" + std::to_string(index) + "," + std::to_string(status) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::ToolDO(int index, int status)
{
    std::string str = "ToolDO(" + std::to_string(index) + "," + std::to_string(status) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::ToolDOInstant(int index, int status)
{
    std::string str = "ToolDOInstant(" + std::to_string(index) + "," + std::to_string(status) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::AO(int index, int status)
{
    std::string str = "AO(" + std::to_string(index) + "," + std::to_string(status) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::AOInstant(int index, int status)
{
    std::string str = "AOInstant(" + std::to_string(index) + "," + std::to_string(status) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::AccJ(int Rprecent)
{
    std::string str = "AccJ(" + std::to_string(Rprecent) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::AccL(int Rprecent)
{
    std::string str = "AccL(" + std::to_string(Rprecent) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::VelJ(int Rprecent)
{
    std::string str = "VelJ(" + std::to_string(Rprecent) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::VelL(int Rprecent)
{
    std::string str = "VelL(" + std::to_string(Rprecent) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::CP(int Rprecent)
{
    std::string str = "CP(" + std::to_string(Rprecent) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::SetArmOrientation(int LorR)
{
    std::string str = "SetArmOrientation(" + std::to_string(LorR) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::SetArmOrientation(int LorR, int UorD, int ForN, int Config6)
{
    std::string str = "SetArmOrientation(" + std::to_string(LorR) + "," + std::to_string(UorD) + "," +
                      std::to_string(ForN) + "," + std::to_string(Config6) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::RunScript(std::string projectName)
{
    std::string str = "RunScript(" + std::string(projectName) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::Stop()
{
    std::string str = "Stop()";

    return SendRecvMsg(str);
};

std::string CDashboard::Pause()
{
    std::string str = "Pause()";

    return SendRecvMsg(str);
};

std::string CDashboard::Continue()
{
    std::string str = "Continue()";

    return SendRecvMsg(str);
};

std::string CDashboard::SetPayload(float load)
{
    std::string str = "SetPayload(" + std::to_string(load) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::SetPayload(std::string name)
{
    std::string str = "SetPayload(" + std::string(name) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::PositiveKin(const CDescartesPoint& pt, int User, int Tool)
{
    std::string str = "PositiveKin(" + std::to_string(pt.x) + "," + std::to_string(pt.y) + "," + std::to_string(pt.z) +
                      "," + std::to_string(pt.rx) + "," + std::to_string(pt.ry) + "," + std::to_string(pt.y) + "," +
                      std::to_string(User) + "," + std::to_string(Tool) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::InverseKin(const CDescartesPoint& pt, int User, int Tool)
{
    std::string str = "InverseKin(" + std::to_string(pt.x) + "," + std::to_string(pt.y) + "," + std::to_string(pt.z) +
                      "," + std::to_string(pt.rx) + "," + std::to_string(pt.ry) + "," + std::to_string(pt.y) + "," +
                      std::to_string(User) + "," + std::to_string(Tool) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::SetCollisionLevel(int level)
{
    std::string str = "SetCollisionLevel(" + std::to_string(level) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::GetAngle()
{
    std::string str = "GetAngle()";

    return SendRecvMsg(str);
};

std::string CDashboard::GetPose()
{
    std::string str = "GetPose()";

    return SendRecvMsg(str);
};

std::string CDashboard::GetPose(int user, int tool)
{
    std::string str = "GetPose(" + std::to_string(user) + "," + std::to_string(tool) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::ModbusRTUCreate(int slave_id, int baud)
{
    std::string str = "ModbusRTUCreate(" + std::to_string(slave_id) + "," + std::to_string(baud) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::ModbusCreate(std::string ip, int port, int slave_id)
{
    std::string str = "ModbusCreate(" + std::string(ip) + "," + std::to_string(port) + std::to_string(slave_id) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::ModbusCreate(std::string ip, int port, int slave_id, int isRTU)
{
    std::string str = "ModbusCreate(" + std::string(ip) + "," + std::to_string(port) + std::to_string(slave_id) +
                      std::to_string(isRTU) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::ModbusClose(int index)
{
    std::string str = "ModbusClose(" + std::to_string(index) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::GetInBits(int index, int addr, int count)
{
    std::string str =
        "GetInBits(" + std::to_string(index) + "," + std::to_string(addr) + "," + std::to_string(count) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::GetInRegs(int index, int addr, int count)
{
    std::string str =
        "GetInRegs(" + std::to_string(index) + "," + std::to_string(addr) + "," + std::to_string(count) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::GetInRegs(int index, int addr, int count, std::string valType)
{
    std::string str = "GetInRegs(" + std::to_string(index) + "," + std::to_string(addr) + "," + std::to_string(count) +
                      "," + std::string(valType) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::GetCoils(int index, int addr, int count)
{
    std::string str =
        "GetCoils(" + std::to_string(index) + "," + std::to_string(addr) + "," + std::to_string(count) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::SetCoils(int index, int addr, int count, std::string valTab)
{
    std::string str = "SetCoils(" + std::to_string(index) + "," + std::to_string(addr) + "," + std::to_string(count) +
                      "," + std::string(valTab) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::GetHoldRegs(int index, int addr, int count)
{
    std::string str =
        "GetHoldRegs(" + std::to_string(index) + "," + std::to_string(addr) + "," + std::to_string(count) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::GetHoldRegs(int index, int addr, int count, std::string valType)
{
    std::string str = "GetHoldRegs(" + std::to_string(index) + "," + std::to_string(addr) + "," +
                      std::to_string(count) + "," + std::string(valType) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::SetHoldRegs(int index, int addr, int count, std::string valTab)
{
    std::string str = "SetHoldRegs(" + std::to_string(index) + "," + std::to_string(addr) + "," +
                      std::to_string(count) + "," + std::string(valTab) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::SetHoldRegs(int index, int addr, int count, std::string valTab, std::string valType)
{
    std::string str = "SetHoldRegs(" + std::to_string(index) + "," + std::to_string(addr) + "," +
                      std::to_string(count) + "," + std::string(valTab) + "," + std::string(valType) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::DI(int index)
{
    std::string str = "DI(" + std::to_string(index) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::ToolDI(int index)
{
    std::string str = "ToolDI(" + std::to_string(index) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::AI(int index)
{
    std::string str = "AI(" + std::to_string(index) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::ToolAI(int index)
{
    std::string str = "ToolAI(" + std::to_string(index) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::DIGroup(int index, int value)
{
    std::ostringstream oss;
    oss << "DIGroup(" + std::to_string(index) + "," + std::to_string(value) + ")";
    std::string str = oss.str();

    return SendRecvMsg(str);
}

std::string CDashboard::DOGroup(int index, int value)
{
    std::ostringstream oss;
    oss << "DOGroup(" + std::to_string(index) + "," + std::to_string(value) + ")";
    std::string str = oss.str();

    return SendRecvMsg(str);
}

std::string CDashboard::BrakeControl(int axisID, int value)
{
    std::string str = "BrakeControl(" + std::to_string(axisID) + "," + std::to_string(value) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::StartDrag()
{
    std::ostringstream oss;
    std::string str = "StartDrag()";

    return SendRecvMsg(str);
};

std::string CDashboard::StopDrag()
{
    std::ostringstream oss;
    std::string str = "StopDrag()";

    return SendRecvMsg(str);
};

std::string CDashboard::DragSensivity(int index, int value)
{
    std::ostringstream oss;
    std::string str = "DragSensivity(" + std::to_string(index) + "," + std::to_string(value) + ")";

    return SendRecvMsg(str);
};

std::string CDashboard::GetDO(int index)
{
    std::ostringstream oss;
    std::string str = "GetDO(" + std::to_string(index) + ")";

    return SendRecvMsg(str);
}
std::string CDashboard::GetAO(int index)
{
    std::ostringstream oss;
    std::string str = "GetAO(" + std::to_string(index) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::SetTool485(int baudrate)
{
    std::ostringstream oss;
    std::string str = "SetTool485(" + std::to_string(baudrate) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::SetSafeWallEnable(int index, int value)
{
    std::ostringstream oss;
    std::string str = "SetSafeWallEnable(" + std::to_string(index) + "," + std::to_string(value) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::SetToolPower(int status)
{
    std::ostringstream oss;
    std::string str = "SetToolPower(" + std::to_string(status) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::SetToolMode(int mode)
{
    std::ostringstream oss;
    std::string str = "SetToolMode(" + std::to_string(mode) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::SetBackDistance(double distance)
{
    std::ostringstream oss;
    std::string str = "SetBackDistance(" + std::to_string(distance) + ")";

    return SendRecvMsg(str);
}
std::string CDashboard::SetPostCollisionMode(int mode)
{
    std::ostringstream oss;
    std::string str = "SetPostCollisionMode(" + std::to_string(mode) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::SetUser(int index, std::string value)
{
    std::ostringstream oss;
    std::string str = "SetUser(" + std::to_string(index) + "," + std::string(value) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::SetTool(int index, std::string value)
{
    std::ostringstream oss;
    std::string str = "SetTool(" + std::to_string(index) + "," + std::string(value) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::CalcUser(int index, int matrix, std::string offset)
{
    std::ostringstream oss;
    std::string str =
        "CalcUser(" + std::to_string(index) + "," + std::to_string(matrix) + "," + std::string(offset) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::CalcTool(int index, int matrix, std::string offset)
{
    std::ostringstream oss;
    std::string str =
        "CalcTool(" + std::to_string(index) + "," + std::to_string(matrix) + "," + std::string(offset) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::GetInputBool(int address)
{
    std::ostringstream oss;
    std::string str = "GetInputBool(" + std::to_string(address) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::GetInputInt(int address)
{
    std::ostringstream oss;
    std::string str = "GetInputInt(" + std::to_string(address) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::GetInputFloat(int address)
{
    std::ostringstream oss;
    std::string str = "GetInputFloat(" + std::to_string(address) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::GetOutputBool(int address)
{
    std::ostringstream oss;
    std::string str = "GetOutputBool(" + std::to_string(address) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::GetOutputInt(int address)
{
    std::ostringstream oss;
    std::string str = "GetOutputInt(" + std::to_string(address) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::GetOutputFloat(int address)
{
    std::ostringstream oss;
    std::string str = "GetOutputFloat(" + std::to_string(address) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::SetOutputBool(int address, int value)
{
    std::ostringstream oss;
    std::string str = "SetOutputBool(" + std::to_string(address) + "," + std::to_string(value) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::SetOutputInt(int address, int value)
{
    std::ostringstream oss;
    std::string str = "SetOutputInt(" + std::to_string(address) + "," + std::to_string(value) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::SetOutputFloat(int address, int value)
{
    std::ostringstream oss;
    std::string str = "SetOutputFloat(" + std::to_string(address) + "," + std::to_string(value) + ")";

    return SendRecvMsg(str);
}

/// @brief
/// @param pt
/// @return
std::string CDashboard::MovJ(const CDescartesPoint& pt)
{
    char cmd[200];
    snprintf(cmd, sizeof(cmd), "MovJ(pose={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f})", pt.x, pt.y, pt.z, pt.rx, pt.ry,
             pt.rz);

    return SendRecvMsg(cmd);
}

std::string CDashboard::MovJ(const CJointPoint& pt)
{
    char cmd[200];
    snprintf(cmd, sizeof(cmd), "MovJ(joint={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f})", pt.j1, pt.j2, pt.j3, pt.j4, pt.j5,
             pt.j6);

    return SendRecvMsg(cmd);
}

std::string CDashboard::MovL(const CDescartesPoint& pt)
{
    char cmd[200];
    snprintf(cmd, sizeof(cmd), "MovL(pose={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f})", pt.x, pt.y, pt.z, pt.rx, pt.ry,
             pt.rz);

    return SendRecvMsg(cmd);
}

std::string CDashboard::MovL(const CJointPoint& pt)
{
    char cmd[200];
    snprintf(cmd, sizeof(cmd), "MovL(joint={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f})", pt.j1, pt.j2, pt.j3, pt.j4, pt.j5,
             pt.j6);

    return SendRecvMsg(cmd);
}

std::string CDashboard::MovLIO(const CDescartesPoint& pt, ModeDistanceIndexStatus& mdis)
{
    char cmd[200];
    snprintf(cmd, sizeof(cmd), "MovLIO(pose={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},%s)", pt.x, pt.y, pt.z, pt.rx, pt.ry,
             pt.rz, mdis.ToString().c_str());

    return SendRecvMsg(cmd);
}

std::string CDashboard::MovLIO(const CJointPoint& pt, ModeDistanceIndexStatus& mdis)
{
    char cmd[200];
    snprintf(cmd, sizeof(cmd), "MovLIO(joint={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},%s)", pt.j1, pt.j2, pt.j3, pt.j4,
             pt.j5, pt.j6, mdis.ToString().c_str());

    return SendRecvMsg(cmd);
}

std::string CDashboard::MovJIO(const CDescartesPoint& pt, ModeDistanceIndexStatus& mdis)
{
    char cmd[200];
    snprintf(cmd, sizeof(cmd), "MovJIO(pose={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},%s)", pt.x, pt.y, pt.z, pt.rx, pt.ry,
             pt.rz, mdis.ToString().c_str());

    return SendRecvMsg(cmd);
}

std::string CDashboard::MovJIO(const CJointPoint& pt, ModeDistanceIndexStatus& mdis)
{
    char cmd[200];
    snprintf(cmd, sizeof(cmd), "MovJIO(joint={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},%s)", pt.j1, pt.j2, pt.j3, pt.j4,
             pt.j5, pt.j6, mdis.ToString().c_str());

    return SendRecvMsg(cmd);
}

std::string CDashboard::Arc(const CDescartesPoint& pt, const CDescartesPoint& pt2)
{
    char cmd[200];
    snprintf(cmd, sizeof(cmd),
             "Arc(pose={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},pose={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f})", pt.x, pt.y,
             pt.z, pt.rx, pt.ry, pt.rz, pt2.x, pt2.y, pt2.z, pt2.rx, pt2.ry, pt2.rz);

    return SendRecvMsg(cmd);
}

std::string CDashboard::Arc(const CJointPoint& pt, const CJointPoint& pt2)
{
    char cmd[200];
    snprintf(cmd, sizeof(cmd),
             "Arc(joint={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},joint={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f})", pt.j1,
             pt.j2, pt.j3, pt.j4, pt.j5, pt.j6, pt2.j1, pt2.j2, pt2.j3, pt2.j4, pt2.j5, pt2.j6);

    return SendRecvMsg(cmd);
}

std::string CDashboard::Circle(const CDescartesPoint& pt, const CDescartesPoint& pt2, int count)
{
    char cmd[200];
    snprintf(cmd, sizeof(cmd),
             "Circle(pose={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},pose={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},%d)", pt.x,
             pt.y, pt.z, pt.rx, pt.ry, pt.rz, pt2.x, pt2.y, pt2.z, pt2.rx, pt2.ry, pt2.rz, count);

    return SendRecvMsg(cmd);
}

std::string CDashboard::Circle(const CJointPoint& pt, const CJointPoint& pt2, int count)
{
    char cmd[200];
    snprintf(cmd, sizeof(cmd),
             "Circle(joint={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},joint={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},%d)",
             pt.j1, pt.j2, pt.j3, pt.j4, pt.j5, pt.j6, pt2.j1, pt2.j2, pt2.j3, pt2.j4, pt2.j5, pt2.j6, count);

    return SendRecvMsg(cmd);
}

// 重载函数
std::string CDashboard::MoveJog(std::string traceName)
{
    std::string str = "MoveJog(" + std::string(traceName) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::StopMoveJog()
{
    std::string str = "MoveJog()";

    return SendRecvMsg(str);
}

std::string CDashboard::StartPath(std::string traceName)
{
    std::string str = "StartPath(" + std::string(traceName) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::GetStartPose(std::string traceName)
{
    std::string str = "GetStartPose(" + std::string(traceName) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::RelMovJTool(const CDescartesPoint& pt)
{
    std::ostringstream oss;
    oss << "RelMovJTool(" << pt.x << ',' << pt.y << ',' << pt.z << ',' << pt.rx << ',' << pt.ry << ',' << pt.rz << ')';
    std::string str = oss.str();

    return SendRecvMsg(str);
}

std::string CDashboard::RelMovLTool(const CDescartesPoint& pt)
{
    std::ostringstream oss;
    oss << "RelMovLTool(" << pt.x << ',' << pt.y << ',' << pt.z << ',' << pt.rx << ',' << pt.ry << ',' << pt.rz << ')';
    std::string str = oss.str();

    return SendRecvMsg(str);
}

std::string CDashboard::RelMovJUser(const CDescartesPoint& pt)
{
    std::ostringstream oss;
    oss << "RelMovJUser(" << pt.x << ',' << pt.y << ',' << pt.z << ',' << pt.rx << ',' << pt.ry << ',' << pt.rz << ')';
    std::string str = oss.str();

    return SendRecvMsg(str);
}

std::string CDashboard::RelMovLUser(const CDescartesPoint& pt)
{
    std::ostringstream oss;
    oss << "RelMovLUser(" << pt.x << ',' << pt.y << ',' << pt.z << ',' << pt.rx << ',' << pt.ry << ',' << pt.rz << ')';
    std::string str = oss.str();

    return SendRecvMsg(str);
}

std::string CDashboard::RelJointMovJ(const CJointPoint& pt)
{
    std::ostringstream oss;
    oss << "RelJointMovJ(" << pt.j1 << ',' << pt.j2 << ',' << pt.j3 << ',' << pt.j4 << ',' << pt.j5 << ',' << pt.j6
        << ')';
    std::string str = oss.str();

    return SendRecvMsg(str);
}

std::string CDashboard::GetCurrentCommandId()
{
    std::string str = "GetCurrentCommandId()";

    return SendRecvMsg(str);
}

std::string CDashboard::EnableSafeSkin(int EnableSafeSkin)
{
    std::string str = "EnableSafeSkin(" + std::to_string(EnableSafeSkin) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::SetSafeSkin(int part, int status)
{
    std::string str = "SetSafeSkin(" + std::to_string(part) + "," + std::to_string(status) + ")";

    return SendRecvMsg(str);
}

std::string CDashboard::ServoJ(const CJointPoint& pt)
{
    std::ostringstream oss;
    oss << "ServoJ(" << pt.j1 << ',' << pt.j2 << ',' << pt.j3 << ',' << pt.j4 << ',' << pt.j5 << ',' << pt.j6 << ')';
    std::string str = oss.str();

    return SendRecvMsg(str);
}

std::string CDashboard::ServoP(const CDescartesPoint& pt)
{
    std::ostringstream oss;
    oss << "ServoP(" << pt.x << ',' << pt.y << ',' << pt.z << ',' << pt.rx << ',' << pt.ry << ',' << pt.rz << ')';
    std::string str = oss.str();

    return SendRecvMsg(str);
}

}    // namespace Dobot