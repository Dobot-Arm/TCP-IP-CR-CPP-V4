#pragma once

#include "ErrorInfoBean.h"

namespace Dobot
{
    class CErrorInfoHelper
    {
    private:
        static CErrorInfoBeans m_ControllerBeans;
        static CErrorInfoBeans m_ServoBeans;

    public:
        static void ParseControllerJsonFile(std::string strFullFile);
        static void ParseServoJsonFile(std::string strFullFile);

        static bool FindController(int id, CErrorInfoBean& bean);
        static bool FindServo(int id, CErrorInfoBean& bean);
    };
}

