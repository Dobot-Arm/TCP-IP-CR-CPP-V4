#include "DobotClient.h"
#include <iostream>

namespace Dobot
{
CDobotClient::CDobotClient()
{
    Construct();
}

CDobotClient::~CDobotClient()
{
    DestroyConstruct();
}

bool CDobotClient::InitNet()
{
#if (defined(_WIN32) || defined(_WIN64))
    WORD wVer = MAKEWORD(2, 2);
    WSADATA wsd;
    if (0 != WSAStartup(wVer, &wsd)) {
        std::cout << "WSAStartup fail, errcode:" << WSAGetLastError() << std::endl;
        return false;
    }
    if (2 != LOBYTE(wVer) || 2 != HIBYTE(wVer)) {
        std::cout << "winsock is not match version\n";
        return false;
    }
#endif
    return true;
}

void CDobotClient::UinitNet()
{
#if (defined(_WIN32) || defined(_WIN64))
    WSACleanup();
#endif
}

void CDobotClient::Construct()
{
    m_sockListen = INVALID_SOCKET;
    m_iPort = 0;
    m_bIsConnect = false;
}

void CDobotClient::DestroyConstruct()
{
    m_bIsConnect = false;
    if (INVALID_SOCKET != m_sockListen) {
        shutdown(m_sockListen, SD_BOTH);
        closesocket(m_sockListen);
        m_sockListen = INVALID_SOCKET;
    }
}

std::string CDobotClient::GetIp() const
{
    return m_strIp;
}

unsigned short CDobotClient::GetPort() const
{
    return m_iPort;
}

bool CDobotClient::Connect(std::string strIp, unsigned short iPort)
{
    if (INVALID_SOCKET == m_sockListen) {
        m_sockListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (INVALID_SOCKET == m_sockListen) {
#if (defined(_WIN32) || defined(_WIN64))
            printf("create socket Error: (errcode: %d)\n", WSAGetLastError());
#else
            printf("create socket Error: %s (errno: %d)\n", strerror(errno), errno);
#endif
            return false;
        }
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(iPort);
#if ((defined(_WIN32) || defined(_WIN64)) && (_WIN32_WINNT < 0x0600))
    addr.sin_addr.s_addr = inet_addr(strIp.c_str());
#else
    inet_pton(addr.sin_family, strIp.c_str(), &(addr.sin_addr.s_addr));
#endif

    if (SOCKET_ERROR == connect(m_sockListen, (struct sockaddr*)&addr, sizeof(addr))) {
#if (defined(_WIN32) || defined(_WIN64))
        printf("connect Error: (errcode: %d)\n", WSAGetLastError());
#else
        printf("connect Error: %s (errno: %d)\n", strerror(errno), errno);
#endif
        return false;
    }

    m_strIp = strIp;
    m_iPort = iPort;

    m_bIsConnect = true;

    OnConnected();

    return true;
}

void CDobotClient::Disconnect()
{
    m_bIsConnect = false;
    if (INVALID_SOCKET != m_sockListen) {
        shutdown(m_sockListen, SD_BOTH);
        closesocket(m_sockListen);
        m_sockListen = INVALID_SOCKET;
        OnDisconnected();
    }
}

bool CDobotClient::IsConnected() const
{
    return m_bIsConnect;
}

bool CDobotClient::SendData(std::string str)
{
    if (!IsConnected()) {
        return false;
    }
    const char* pszData = str.c_str();
    size_t iHasWrite = 0;
    do {
        int iWrite = send(m_sockListen, pszData + iHasWrite, str.length() - iHasWrite, 0);
        if (iWrite <= 0) {
#if (defined(_WIN32) || defined(_WIN64))
            printf("connect Error: (errcode: %d)\n", WSAGetLastError());
#else
            printf("connect Error: %s (errno: %d)\n", strerror(errno), errno);
#endif
            Disconnect();
            return false;
        }
        iHasWrite += iWrite;
    } while (iHasWrite < str.length());
    return true;
}

std::string CDobotClient::WaitReply(int iTimeoutMillsecond)
{
    fd_set fdRead;
    FD_ZERO(&fdRead);
    FD_SET(m_sockListen, &fdRead);
    struct timeval tv;
    tv.tv_sec = iTimeoutMillsecond / 1000;
    tv.tv_usec = (iTimeoutMillsecond % 1000) * 1000;
#if (defined(_WIN32) || defined(_WIN64))
    int iRet = select(fdRead.fd_count, &fdRead, nullptr, nullptr, &tv);
    if (iRet < 0) {
        printf("connect Error: (errcode: %d)\n", WSAGetLastError());
    }
#else
    int iRet = select(m_sockListen + 1, &fdRead, nullptr, nullptr, &tv);
    if (iRet < 0) {
        printf("select Error: %s (errno: %d)\n", strerror(errno), errno);
    }
#endif
    if (iRet < 0) {
        Disconnect();
        return "";
    } else if (0 == iRet) {    // timeout,do nothing
        return "";
    }

    char szBuf[1024] = "";
    int iLen = 1023;
    int iRead = recv(m_sockListen, szBuf, iLen, 0);
    if (iRead <= 0) {
        Disconnect();
        return "";
    }
    return std::string(szBuf);
}

int CDobotClient::Receive(char* pBuffer, int iLen)
{
    int iRead = recv(m_sockListen, pBuffer, iLen, 0);
    if (iRead <= 0) {
        Disconnect();
    }
    return iRead;
}
}    // namespace Dobot
