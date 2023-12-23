#include "ErrorInfoHelper.h"

#include <fstream>
#include <iostream>

namespace Dobot
{
CErrorInfoBeans CErrorInfoHelper::m_ControllerBeans;
CErrorInfoBeans CErrorInfoHelper::m_ServoBeans;

void CErrorInfoHelper::ParseControllerJsonFile(std::string strFullFile)
{
    std::ifstream ifs;
    ifs.open(strFullFile.c_str());
    if (!ifs.is_open()) {
        std::cout << "open file :" << strFullFile << "fail" << std::endl;
        return;
    }
    std::string strJson;
    while (!ifs.eof()) {
        std::string s;
        std::getline(ifs, s);
        strJson += s;
    }
    m_ControllerBeans.FromJson(strJson);
}

void CErrorInfoHelper::ParseServoJsonFile(std::string strFullFile)
{
    std::ifstream ifs;
    ifs.open(strFullFile.c_str());
    if (!ifs.is_open()) {
        std::cout << "open file :" << strFullFile << "fail" << std::endl;
        return;
    }
    std::string strJson;
    while (!ifs.eof()) {
        std::string s;
        std::getline(ifs, s);
        strJson += s;
    }
    m_ServoBeans.FromJson(strJson);
}

bool CErrorInfoHelper::FindController(int id, CErrorInfoBean& bean)
{
    if (m_ControllerBeans.errorInfos.find(id) != m_ControllerBeans.errorInfos.end()) {
        bean = m_ControllerBeans.errorInfos[id];
        return true;
    }
    return false;
}

bool CErrorInfoHelper::FindServo(int id, CErrorInfoBean& bean)
{
    if (m_ServoBeans.errorInfos.find(id) != m_ServoBeans.errorInfos.end()) {
        bean = m_ServoBeans.errorInfos[id];
        return true;
    }
    return false;
}
}    // namespace Dobot