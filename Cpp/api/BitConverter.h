#pragma once

#include <cstdint>

namespace Dobot
{
    class CBitConverter
    {
    public:
        static short ToShort(char* pBuffer);
        static unsigned short ToUShort(char* pBuffer);

        static int ToInt(char* pBuffer);
        static unsigned int ToUInt(char* pBuffer);

        static long ToLong(char* pBuffer);
        static unsigned long ToULong(char* pBuffer);

        static int64_t ToInt64(char* pBuffer);
        static uint64_t ToUInt64(char* pBuffer);

        static float ToFloat(char* pBuffer);

        static double ToDouble(char* pBuffer);
    };
}

