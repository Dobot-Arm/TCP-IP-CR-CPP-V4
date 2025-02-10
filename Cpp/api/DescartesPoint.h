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

struct CForcePoint
{
    public:
        /// <summary>
        /// X 轴目标力，单位：毫米
        /// </summary>
        double fx;

        /// <summary>
        /// Y 轴目标力，单位：毫米
        /// </summary>
        double fy;

        /// <summary>
        /// Z 轴目标力，单位：毫米
        /// </summary>
        double fz;

        /// <summary>
        /// Rx 轴目标力，单位：度
        /// </summary>
        double frx;

        /// <summary>
        /// Ry 轴目标力，单位：度
        /// </summary>
        double fry;

        /// <summary>
        /// Rz 轴目标力，单位：度
        /// </summary>
        double frz;

        std::string ToString()
        {
            std::ostringstream oss;
            oss << fx << ',' << fy << ',' << fz << ',' << frx << ',' << fry << ',' << frz;
            return oss.str();
        }
};

struct COffsetPoint
{
    public:
        /// <summary>
        /// X 轴偏移量
        /// </summary>
        double offsetX;

        /// <summary>
        /// Y 轴偏移量
        /// </summary>
        double offsetY;

        /// <summary>
        /// Z 轴偏移量
        /// </summary>
        double offsetZ;

        /// <summary>
        /// Rx 轴偏移量
        /// </summary>
        double offsetRx;

        /// <summary>
        /// Ry 轴偏移量
        /// </summary>
        double offsetRy;

        /// <summary>
        /// Rz 轴偏移量
        /// </summary>
        double offsetRz;

        std::string ToString()
        {
            std::ostringstream oss;
            oss << offsetX << ',' << offsetY << ',' << offsetZ << ',' << offsetRx << ',' << offsetRy << ',' << offsetRz;
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
