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

std::string CDashboard::ClearError()
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "ClearError()";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::PowerOn()
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "PowerOn()";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(15000);
}

std::string CDashboard::EmergencyStop(int value)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "EmergencyStop(" + std::to_string(value) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(15000);
}

std::string CDashboard::EnableRobot()
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "EnableRobot()";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(20000);
}

std::string CDashboard::DisableRobot()
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "DisableRobot()";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(20000);
}

std::string CDashboard::SpeedFactor(int ratio)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    oss << "SpeedFactor(" << ratio << ")";
    std::string str = oss.str();
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::GetErrorID()
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "GetErrorID()";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::User(int index)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "User(" + std::to_string(index) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::Tool(int index)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "Tool(" + std::to_string(index) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::RobotMode()
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "RobotMode()";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::PayLoad(double weight, double inertia)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "PayLoad(" + std::to_string(weight) + "," + std::to_string(inertia) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::DO(int index, int status)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "DO(" + std::to_string(index) + "," + std::to_string(status) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::DO(int index, int status, int time)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "DO(" + std::to_string(index) + "," + std::to_string(status) + "," + std::to_string(time) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::DOInstant(int index, int status)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "DOInstant(" + std::to_string(index) + "," + std::to_string(status) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::ToolDO(int index, int status)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "ToolDO(" + std::to_string(index) + "," + std::to_string(status) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::ToolDOInstant(int index, int status)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "ToolDOInstant(" + std::to_string(index) + "," + std::to_string(status) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::AO(int index, int status)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "AO(" + std::to_string(index) + "," + std::to_string(status) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::AOInstant(int index, int status)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "AOInstant(" + std::to_string(index) + "," + std::to_string(status) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::AccJ(int Rprecent)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "AccJ(" + std::to_string(Rprecent) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::AccL(int Rprecent)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "AccL(" + std::to_string(Rprecent) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::VelJ(int Rprecent)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "VelJ(" + std::to_string(Rprecent) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::VelL(int Rprecent)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "VelL(" + std::to_string(Rprecent) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::CP(int Rprecent)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "CP(" + std::to_string(Rprecent) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::SetArmOrientation(int LorR)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "SetArmOrientation(" + std::to_string(LorR) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::SetArmOrientation(int LorR, int UorD, int ForN, int Config6)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "SetArmOrientation(" + std::to_string(LorR) + "," + std::to_string(UorD) + "," +
                      std::to_string(ForN) + "," + std::to_string(Config6) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::RunScript(std::string projectName)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "RunScript(" + std::string(projectName) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::Stop()
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "Stop()";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::Pause()
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "Pause()";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::Continue()
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "Continue()";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::SetPayload(float load)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "SetPayload(" + std::to_string(load) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::SetPayload(std::string name)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "SetPayload(" + std::string(name) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::PositiveKin(const CDescartesPoint& pt, int User, int Tool)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "PositiveKin(" + std::to_string(pt.x) + "," + std::to_string(pt.y) + "," + std::to_string(pt.z) +
                      "," + std::to_string(pt.rx) + "," + std::to_string(pt.ry) + "," + std::to_string(pt.y) + "," +
                      std::to_string(User) + "," + std::to_string(Tool) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::InverseKin(const CDescartesPoint& pt, int User, int Tool)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "InverseKin(" + std::to_string(pt.x) + "," + std::to_string(pt.y) + "," + std::to_string(pt.z) +
                      "," + std::to_string(pt.rx) + "," + std::to_string(pt.ry) + "," + std::to_string(pt.y) + "," +
                      std::to_string(User) + "," + std::to_string(Tool) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::SetCollisionLevel(int level)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "SetCollisionLevel(" + std::to_string(level) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::GetAngle()
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "GetAngle()";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::GetPose()
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "GetPose()";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::GetPose(int user, int tool)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "GetPose(" + std::to_string(user) + "," + std::to_string(tool) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::ModbusRTUCreate(int slave_id, int baud)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "ModbusRTUCreate(" + std::to_string(slave_id) + "," + std::to_string(baud) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::ModbusCreate(std::string ip, int port, int slave_id)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "ModbusCreate(" + std::string(ip) + "," + std::to_string(port) + std::to_string(slave_id) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::ModbusCreate(std::string ip, int port, int slave_id, int isRTU)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "ModbusCreate(" + std::string(ip) + "," + std::to_string(port) + std::to_string(slave_id) +
                      std::to_string(isRTU) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::ModbusClose(int index)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "ModbusClose(" + std::to_string(index) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::GetInBits(int index, int addr, int count)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str =
        "GetInBits(" + std::to_string(index) + "," + std::to_string(addr) + "," + std::to_string(count) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::GetInRegs(int index, int addr, int count)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str =
        "GetInRegs(" + std::to_string(index) + "," + std::to_string(addr) + "," + std::to_string(count) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::GetInRegs(int index, int addr, int count, std::string valType)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "GetInRegs(" + std::to_string(index) + "," + std::to_string(addr) + "," + std::to_string(count) +
                      "," + std::string(valType) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::GetCoils(int index, int addr, int count)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str =
        "GetCoils(" + std::to_string(index) + "," + std::to_string(addr) + "," + std::to_string(count) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::SetCoils(int index, int addr, int count, std::string valTab)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "SetCoils(" + std::to_string(index) + "," + std::to_string(addr) + "," + std::to_string(count) +
                      "," + std::string(valTab) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::GetHoldRegs(int index, int addr, int count)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str =
        "GetHoldRegs(" + std::to_string(index) + "," + std::to_string(addr) + "," + std::to_string(count) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::GetHoldRegs(int index, int addr, int count, std::string valType)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "GetHoldRegs(" + std::to_string(index) + "," + std::to_string(addr) + "," +
                      std::to_string(count) + "," + std::string(valType) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::SetHoldRegs(int index, int addr, int count, std::string valTab)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "SetHoldRegs(" + std::to_string(index) + "," + std::to_string(addr) + "," +
                      std::to_string(count) + "," + std::string(valTab) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::SetHoldRegs(int index, int addr, int count, std::string valTab, std::string valType)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "SetHoldRegs(" + std::to_string(index) + "," + std::to_string(addr) + "," +
                      std::to_string(count) + "," + std::string(valTab) + "," + std::string(valType) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::DI(int index)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "DI(" + std::to_string(index) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::ToolDI(int index)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "ToolDI(" + std::to_string(index) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::AI(int index)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "AI(" + std::to_string(index) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::ToolAI(int index)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "ToolAI(" + std::to_string(index) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::DIGroup(int index, int value)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    oss << "DIGroup(" + std::to_string(index) + "," + std::to_string(value) + ")";
    std::string str = oss.str();
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::DOGroup(int index, int value)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    oss << "DOGroup(" + std::to_string(index) + "," + std::to_string(value) + ")";
    std::string str = oss.str();
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::BrakeControl(int axisID, int value)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "BrakeControl(" + std::to_string(axisID) + "," + std::to_string(value) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::StartDrag()
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "StartDrag()";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::StopDrag()
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "StopDrag()";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::DragSensivity(int index, int value)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "DragSensivity(" + std::to_string(index) + "," + std::to_string(value) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
};

std::string CDashboard::GetDO(int index)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "GetDO(" + std::to_string(index) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}
std::string CDashboard::GetAO(int index)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "GetAO(" + std::to_string(index) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::SetTool485(int baudrate)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "SetTool485(" + std::to_string(baudrate) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::SetSafeWallEnable(int index, int value)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "SetSafeWallEnable(" + std::to_string(index) + "," + std::to_string(value) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::SetToolPower(int status)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "SetToolPower(" + std::to_string(status) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::SetToolMode(int mode)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "SetToolMode(" + std::to_string(mode) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::SetBackDistance(double distance)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "SetBackDistance(" + std::to_string(distance) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}
std::string CDashboard::SetPostCollisionMode(int mode)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "SetPostCollisionMode(" + std::to_string(mode) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::SetUser(int index, std::string value)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "SetUser(" + std::to_string(index) + "," + std::string(value) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::SetTool(int index, std::string value)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "SetTool(" + std::to_string(index) + "," + std::string(value) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::CalcUser(int index, int matrix, std::string offset)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str =
        "CalcUser(" + std::to_string(index) + "," + std::to_string(matrix) + "," + std::string(offset) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::CalcTool(int index, int matrix, std::string offset)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str =
        "CalcTool(" + std::to_string(index) + "," + std::to_string(matrix) + "," + std::string(offset) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::GetInputBool(int address)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "GetInputBool(" + std::to_string(address) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::GetInputInt(int address)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "GetInputInt(" + std::to_string(address) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::GetInputFloat(int address)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "GetInputFloat(" + std::to_string(address) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::GetOutputBool(int address)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "GetOutputBool(" + std::to_string(address) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::GetOutputInt(int address)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "GetOutputInt(" + std::to_string(address) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::GetOutputFloat(int address)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "GetOutputFloat(" + std::to_string(address) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::SetOutputBool(int address, int value)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "SetOutputBool(" + std::to_string(address) + "," + std::to_string(value) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::SetOutputInt(int address, int value)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "SetOutputInt(" + std::to_string(address) + "," + std::to_string(value) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::SetOutputFloat(int address, int value)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    std::string str = "SetOutputFloat(" + std::to_string(address) + "," + std::to_string(value) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

/// @brief
/// @param pt
/// @return
std::string CDashboard::MovJ(const CDescartesPoint& pt)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    char cmd[200];
    snprintf(cmd, sizeof(cmd), "MovJ(pose={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f})", pt.x, pt.y, pt.z, pt.rx, pt.ry,
             pt.rz);

    if (!SendData(cmd)) {
        strcat(cmd, ":send error");
        return cmd;
    }

    return WaitReply(5000);
}

std::string CDashboard::MovJ(const CJointPoint& pt)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    char cmd[200];
    snprintf(cmd, sizeof(cmd), "MovJ(joint={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f})", pt.j1, pt.j2, pt.j3, pt.j4, pt.j5,
             pt.j6);

    if (!SendData(cmd)) {
        strcat(cmd, ":send error");
        return cmd;
    }

    return WaitReply(5000);
}

std::string CDashboard::MovL(const CDescartesPoint& pt)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    char cmd[200];
    snprintf(cmd, sizeof(cmd), "MovL(pose={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f})", pt.x, pt.y, pt.z, pt.rx, pt.ry,
             pt.rz);

    if (!SendData(cmd)) {
        strcat(cmd, ":send error");
        return cmd;
    }

    return WaitReply(5000);
}

std::string CDashboard::MovL(const CJointPoint& pt)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    char cmd[200];
    snprintf(cmd, sizeof(cmd), "MovL(joint={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f})", pt.j1, pt.j2, pt.j3, pt.j4, pt.j5,
             pt.j6);

    if (!SendData(cmd)) {
        strcat(cmd, ":send error");
        return cmd;
    }

    return WaitReply(5000);
}

std::string CDashboard::MovLIO(const CDescartesPoint& pt, ModeDistanceIndexStatus& mdis)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    char cmd[200];
    snprintf(cmd, sizeof(cmd), "MovLIO(pose={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},%s)", pt.x, pt.y, pt.z, pt.rx, pt.ry,
             pt.rz, mdis.ToString().c_str());

    if (!SendData(cmd)) {
        strcat(cmd, ":send error");
        return cmd;
    }

    return WaitReply(5000);
}

std::string CDashboard::MovLIO(const CJointPoint& pt, ModeDistanceIndexStatus& mdis)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    char cmd[200];
    snprintf(cmd, sizeof(cmd), "MovLIO(joint={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},%s)", pt.j1, pt.j2, pt.j3, pt.j4,
             pt.j5, pt.j6, mdis.ToString().c_str());

    if (!SendData(cmd)) {
        strcat(cmd, ":send error");
        return cmd;
    }

    return WaitReply(5000);
}

std::string CDashboard::MovJIO(const CDescartesPoint& pt, ModeDistanceIndexStatus& mdis)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    char cmd[200];
    snprintf(cmd, sizeof(cmd), "MovJIO(pose={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},%s)", pt.x, pt.y, pt.z, pt.rx, pt.ry,
             pt.rz, mdis.ToString().c_str());

    if (!SendData(cmd)) {
        strcat(cmd, ":send error");
        return cmd;
    }

    return WaitReply(5000);
}

std::string CDashboard::MovJIO(const CJointPoint& pt, ModeDistanceIndexStatus& mdis)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    char cmd[200];
    snprintf(cmd, sizeof(cmd), "MovJIO(joint={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},%s)", pt.j1, pt.j2, pt.j3, pt.j4,
             pt.j5, pt.j6, mdis.ToString().c_str());

    if (!SendData(cmd)) {
        strcat(cmd, ":send error");
        return cmd;
    }

    return WaitReply(5000);
}

std::string CDashboard::Arc(const CDescartesPoint& pt, const CDescartesPoint& pt2)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    char cmd[200];
    snprintf(cmd, sizeof(cmd),
             "Arc(pose={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},pose={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f})", pt.x, pt.y,
             pt.z, pt.rx, pt.ry, pt.rz, pt2.x, pt2.y, pt2.z, pt2.rx, pt2.ry, pt2.rz);

    if (!SendData(cmd)) {
        strcat(cmd, ":send error");
        return cmd;
    }

    return WaitReply(5000);
}

std::string CDashboard::Arc(const CJointPoint& pt, const CJointPoint& pt2)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    char cmd[200];
    snprintf(cmd, sizeof(cmd),
             "Arc(joint={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},joint={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f})", pt.j1,
             pt.j2, pt.j3, pt.j4, pt.j5, pt.j6, pt2.j1, pt2.j2, pt2.j3, pt2.j4, pt2.j5, pt2.j6);

    if (!SendData(cmd)) {
        strcat(cmd, ":send error");
        return cmd;
    }

    return WaitReply(5000);
}

std::string CDashboard::Circle(const CDescartesPoint& pt, const CDescartesPoint& pt2, int count)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    char cmd[200];
    snprintf(cmd, sizeof(cmd),
             "Circle(pose={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},pose={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},%d)", pt.x,
             pt.y, pt.z, pt.rx, pt.ry, pt.rz, pt2.x, pt2.y, pt2.z, pt2.rx, pt2.ry, pt2.rz, count);

    if (!SendData(cmd)) {
        strcat(cmd, ":send error");
        return cmd;
    }

    return WaitReply(5000);
}

std::string CDashboard::Circle(const CJointPoint& pt, const CJointPoint& pt2, int count)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    char cmd[200];
    snprintf(cmd, sizeof(cmd),
             "Circle(joint={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},joint={%0.3f,%0.3f,%0.3f,%0.3f,%0.3f,%0.3f},%d)",
             pt.j1, pt.j2, pt.j3, pt.j4, pt.j5, pt.j6, pt2.j1, pt2.j2, pt2.j3, pt2.j4, pt2.j5, pt2.j6, count);

    if (!SendData(cmd)) {
        strcat(cmd, ":send error");
        return cmd;
    }

    return WaitReply(5000);
}

// 重载函数
std::string CDashboard::MoveJog(std::string traceName)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "MoveJog(" + std::string(traceName) + ")";

    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::StopMoveJog()
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "MoveJog()";

    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::StartPath(std::string traceName)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "StartPath(" + std::string(traceName) + ")";

    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::GetStartPose(std::string traceName)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::string str = "GetStartPose(" + std::string(traceName) + ")";

    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::RelMovJTool(const CDescartesPoint& pt)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    oss << "RelMovJTool(" << pt.x << ',' << pt.y << ',' << pt.z << ',' << pt.rx << ',' << pt.ry << ',' << pt.rz << ')';
    std::string str = oss.str();
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::RelMovLTool(const CDescartesPoint& pt)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    oss << "RelMovLTool(" << pt.x << ',' << pt.y << ',' << pt.z << ',' << pt.rx << ',' << pt.ry << ',' << pt.rz << ')';
    std::string str = oss.str();
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::RelMovJUser(const CDescartesPoint& pt)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    oss << "RelMovJUser(" << pt.x << ',' << pt.y << ',' << pt.z << ',' << pt.rx << ',' << pt.ry << ',' << pt.rz << ')';
    std::string str = oss.str();
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::RelMovLUser(const CDescartesPoint& pt)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    oss << "RelMovLUser(" << pt.x << ',' << pt.y << ',' << pt.z << ',' << pt.rx << ',' << pt.ry << ',' << pt.rz << ')';
    std::string str = oss.str();
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::RelJointMovJ(const CJointPoint& pt)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    oss << "RelJointMovJ(" << pt.j1 << ',' << pt.j2 << ',' << pt.j3 << ',' << pt.j4 << ',' << pt.j5 << ',' << pt.j6
        << ')';
    std::string str = oss.str();
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::GetCurrentCommandId()
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }
    std::string str = "GetCurrentCommandId()";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::EnableSafeSkin(int EnableSafeSkin)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }
    std::string str = "EnableSafeSkin(" + std::to_string(EnableSafeSkin) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::SetSafeSkin(int part, int status)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }
    std::string str = "SetSafeSkin(" + std::to_string(part) + "," + std::to_string(status) + ")";
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::ServoJ(const CJointPoint& pt)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    oss << "ServoJ(" << pt.j1 << ',' << pt.j2 << ',' << pt.j3 << ',' << pt.j4 << ',' << pt.j5 << ',' << pt.j6 << ')';
    std::string str = oss.str();
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

std::string CDashboard::ServoP(const CDescartesPoint& pt)
{
    if (!IsConnected()) {
        return "device does not connected!!!";
    }

    std::ostringstream oss;
    oss << "ServoP(" << pt.x << ',' << pt.y << ',' << pt.z << ',' << pt.rx << ',' << pt.ry << ',' << pt.rz << ')';
    std::string str = oss.str();
    if (!SendData(str)) {
        return str + ":send error";
    }

    return WaitReply(5000);
}

}    // namespace Dobot