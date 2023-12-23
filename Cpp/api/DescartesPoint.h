#pragma once
#include <sstream>
#include <string>

namespace Dobot
{
struct CDescartesPoint
{
public:
    /// <summary>
    /// X 轴位置，单位：毫米
    /// </summary>
    double x;

    /// <summary>
    /// Y 轴位置，单位：毫米
    /// </summary>
    double y;

    /// <summary>
    /// Z 轴位置，单位：毫米
    /// </summary>
    double z;

    /// <summary>
    /// Rx 轴位置，单位：度
    /// </summary>
    double rx;

    /// <summary>
    /// Ry 轴位置，单位：度
    /// </summary>
    double ry;

    /// <summary>
    /// Rz 轴位置，单位：度
    /// </summary>
    double rz;

    std::string ToString()
    {
        std::ostringstream oss;
        oss << x << ',' << y << ',' << z << ',' << rx << ',' << ry << ',' << rz;
        return oss.str();
    }
};

struct ModeDistanceIndexStatus
{
public:
    // 设置Distance模式
    int Mode;

    // 运行指定的距离
    int Distance;

    // 数字输出索引
    int Index;

    // 数字输出状态
    int Status;
    std::string ToString()
    {
        std::ostringstream oss;
        oss << "{" << Mode << ',' << Distance << ',' << Index << ',' << Status << "}";
        return oss.str();
    }
};
}    // namespace Dobot
