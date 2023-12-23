#include "BitConverter.h"

namespace Dobot
{
    short CBitConverter::ToShort(char* pBuffer)
    {
        short value = pBuffer[1]&0xFF;
        value <<= 8;
        value |= pBuffer[0]&0xFF;
        return value;
    }

    unsigned short CBitConverter::ToUShort(char* pBuffer)
    {
        unsigned short value = pBuffer[1]&0xFF;
        value <<= 8;
        value |= pBuffer[0]&0xFF;
        return value;
    }

    int CBitConverter::ToInt(char* pBuffer)
    {
        int value = pBuffer[3]&0xFF;
        value <<= 8;
        value |= pBuffer[2]&0xFF;
        value <<= 8;
        value |= pBuffer[1]&0xFF;
        value <<= 8;
        value |= pBuffer[0]&0xFF;
        return value;
    }

    unsigned int CBitConverter::ToUInt(char* pBuffer)
    {
        unsigned int value = pBuffer[3]&0xFF;
        value <<= 8;
        value |= pBuffer[2]&0xFF;
        value <<= 8;
        value |= pBuffer[1]&0xFF;
        value <<= 8;
        value |= pBuffer[0]&0xFF;
        return value;
    }

    long CBitConverter::ToLong(char* pBuffer)
    {
        long value = pBuffer[3]&0xFF;
        value <<= 8;
        value |= pBuffer[2]&0xFF;
        value <<= 8;
        value |= pBuffer[1]&0xFF;
        value <<= 8;
        value |= pBuffer[0]&0xFF;
        return value;
    }

    unsigned long CBitConverter::ToULong(char* pBuffer)
    {
        unsigned long value = pBuffer[3]&0xFF;
        value <<= 8;
        value |= pBuffer[2]&0xFF;
        value <<= 8;
        value |= pBuffer[1]&0xFF;
        value <<= 8;
        value |= pBuffer[0]&0xFF;
        return value;
    }

    int64_t CBitConverter::ToInt64(char* pBuffer)
    {
        int64_t value = pBuffer[7]&0xFF;
        value <<= 8;
        value |= pBuffer[6]&0xFF;
        value <<= 8;
        value |= pBuffer[5]&0xFF;
        value <<= 8;
        value |= pBuffer[4]&0xFF;
        value <<= 8;
        value |= pBuffer[3]&0xFF;
        value <<= 8;
        value |= pBuffer[2]&0xFF;
        value <<= 8;
        value |= pBuffer[1]&0xFF;
        value <<= 8;
        value |= pBuffer[0]&0xFF;
        return value;
    }

    uint64_t CBitConverter::ToUInt64(char* pBuffer)
    {
        uint64_t value = pBuffer[7];
        value <<= 8;
        value |= pBuffer[6]&0xFF;
        value <<= 8;
        value |= pBuffer[5]&0xFF;
        value <<= 8;
        value |= pBuffer[4]&0xFF;
        value <<= 8;
        value |= pBuffer[3]&0xFF;
        value <<= 8;
        value |= pBuffer[2]&0xFF;
        value <<= 8;
        value |= pBuffer[1]&0xFF;
        value <<= 8;
        value |= pBuffer[0]&0xFF;
        return value;
    }

    float CBitConverter::ToFloat(char* pBuffer)
    {
        union Float
        {
            char ch[4];
            float f;
        };
        Float value;
        value.ch[0] = pBuffer[0];
        value.ch[1] = pBuffer[1];
        value.ch[2] = pBuffer[2];
        value.ch[3] = pBuffer[3];

        return value.f;
    }

    double CBitConverter::ToDouble(char* pBuffer)
    {
        union Double
        {
            char ch[8];
            double f;
        };
        Double value;
        value.ch[0] = pBuffer[0];
        value.ch[1] = pBuffer[1];
        value.ch[2] = pBuffer[2];
        value.ch[3] = pBuffer[3];
        value.ch[4] = pBuffer[4];
        value.ch[5] = pBuffer[5];
        value.ch[6] = pBuffer[6];
        value.ch[7] = pBuffer[7];

        return value.f;
    }
}
