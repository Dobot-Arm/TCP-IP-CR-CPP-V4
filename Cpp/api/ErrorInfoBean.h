#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

namespace Dobot
{
    struct Description
    {
        std::string description;
        std::string cause;
        std::string solution;
    };

    struct CErrorInfoBean
    {
        int id;
        int level;
        std::string Type;
        Description en;
        Description zh_CN;
    };

    class CErrorInfoBeans
    {
    public:
        std::unordered_map<int, CErrorInfoBean> errorInfos;

        bool FromJson(const std::string& strJson);
    };
}