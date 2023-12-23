#include "ErrorInfoBean.h"

#include <iostream>
#include "rapidjson/document.h"

namespace Dobot
{
    bool CErrorInfoBeans::FromJson(const std::string& strJson)
    {
        rapidjson::Document doc;
        doc.Parse(strJson.c_str());
        if (doc.HasParseError())
        {
            std::cout << "is not a json string\n";
            return false;
        }
        if (!doc.IsArray())
        {
            std::cout << "is not a json array\n";
            return false;
        }
        for (int i = 0; i < doc.Size(); ++i)
        {
            CErrorInfoBean bean;

            if (doc[i].HasMember("id") && doc[i]["id"].IsInt())
            {
                bean.id = doc[i]["id"].GetInt();
            }
            if (doc[i].HasMember("level") && doc[i]["level"].IsInt())
            {
                bean.level = doc[i]["level"].GetInt();
            }
            if (doc[i].HasMember("en") && doc[i]["en"].IsObject())
            {
                auto obj = doc[i]["en"].GetObject();
                if (obj.HasMember("description") && obj["description"].IsString())
                {
                    bean.en.description = obj["description"].GetString();
                }
                if (obj.HasMember("cause") && obj["cause"].IsString())
                {
                    bean.en.cause = obj["cause"].GetString();
                }
                if (obj.HasMember("solution") && obj["solution"].IsString())
                {
                    bean.en.solution = obj["solution"].GetString();
                }
            }
            if (doc[i].HasMember("zh_CN") && doc[i]["zh_CN"].IsObject())
            {
                auto obj = doc[i]["zh_CN"].GetObject();
                if (obj.HasMember("description") && obj["description"].IsString())
                {
                    bean.zh_CN.description = obj["description"].GetString();
                }
                if (obj.HasMember("cause") && obj["cause"].IsString())
                {
                    bean.zh_CN.cause = obj["cause"].GetString();
                }
                if (obj.HasMember("solution") && obj["solution"].IsString())
                {
                    bean.zh_CN.solution = obj["solution"].GetString();
                }
            }
            errorInfos[bean.id] = bean;
        }
        return true;
    }
}