#pragma once

#if defined(_WIN32)||defined(_WIN64)
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <netdb.h>
#include <string.h>

#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define ADDR_ANY 0
#define SD_BOTH SHUT_RDWR

#define closesocket close
#define Sleep(t) sleep(t)
#endif

#include <string>

namespace Dobot
{
    class CDobotClient
    {
    public:
        CDobotClient();
        virtual ~CDobotClient();

        static bool InitNet();
        static void UinitNet();

        std::string GetIp() const;
        unsigned short GetPort() const;

        /// <summary>
        /// 连接设备
        /// </summary>
        /// <param name="strIp">设备地址</param>
        /// <param name="iPort">指定端口</param>
        /// <returns>true成功，false失败</returns>
        bool Connect(std::string strIp, unsigned short iPort);

        /// <summary>
        /// 断开连接
        /// </summary>
        void Disconnect();

        bool IsConnected() const;

    protected:
        virtual void OnConnected() = 0;
        virtual void OnDisconnected() = 0;

        void Construct();
        void DestroyConstruct();

        /// <summary>
        /// 发送数据
        /// </summary>
        /// <param name="str">发送内容</param>
        /// <returns>成功-true，失败-false</returns>

        bool SendData(std::string str);

        /// <summary>
        /// 等待响应
        /// </summary>
        /// <param name="iTimeoutMillsecond">等待时间，毫秒单位</param>
        /// <returns>返回响应的内容</returns>
        std::string WaitReply(int iTimeoutMillsecond);

        int Receive(char* pBuffer, int iLen);

    private:
        std::string m_strIp;
        unsigned short m_iPort;
        SOCKET m_sockListen;
        bool m_bIsConnect;
    };
}

