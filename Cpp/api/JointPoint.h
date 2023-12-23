#pragma once
#include <sstream>
#include <string>

namespace Dobot
{
    class CJointPoint
    {
    public:
        /// <summary>
        /// J1 轴位置，单位：度
        /// </summary>
        double j1;

        /// <summary>
        /// J2 轴位置，单位：度
        /// </summary>
        double j2;

        /// <summary>
        /// J3 轴位置，单位：度
        /// </summary>
        double j3;

        /// <summary>
        /// J4 轴位置，单位：度
        /// </summary>
        double j4;

        /// <summary>
        /// J5 轴位置，单位：度
        /// </summary>
        double j5;

        /// <summary>
        /// J6 轴位置，单位：度
        /// </summary>
        double j6;

        std::string ToString()
        {
            std::ostringstream oss;
            oss << j1 << ',' << j2 << ',' << j3 << ',' << j4 << ',' << j5 << ',' << j6;
            return oss.str();
        }
    };
}
