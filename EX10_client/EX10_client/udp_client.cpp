#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS

#include <winsock2.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <atomic>

#pragma comment(lib, "ws2_32.lib")

#define PORT 3500
#define MAX_BUF_SIZE 256

using namespace std;

std::atomic<bool> running(true);

DWORD WINAPI RecvThread(LPVOID param) {
    SOCKET sock = (SOCKET)param;

    SOCKADDR_IN fromAddr{};
    int fromLen = sizeof(fromAddr);

    char buf[MAX_BUF_SIZE + 20]{};

    while (running.load()) {
        ZeroMemory(buf, sizeof(buf));

        int recvLen = recvfrom(sock, buf, MAX_BUF_SIZE + 20, 0,
            (SOCKADDR*)&fromAddr, &fromLen);

        if (recvLen > 0) {
            buf[recvLen] = '\0';
            cout << "\n[서버 수신] " << buf << endl;
            //cout << "> ";   // 입력 프롬프트 다시 보여주기용
        }
    }

    return 0;
}


int main() {
    WSADATA wsdata;

    if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
        cout << "윈도우 소켓 초기화 실패" << endl;
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        cout << "소켓 생성 실패" << endl;
        WSACleanup();
        return 1;
    }

    SOCKADDR_IN serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("192.168.0.63");

    CreateThread(
        nullptr,
        0,
        RecvThread,
        (LPVOID)clientSocket,
        0,
        nullptr
    );

    int serverAddrSize = sizeof(serverAddress);

    string msg_str;
    string id_str;
    string s_msg_str;

    // 서버에 첫 메시지(접속 알림용)
    const char* hello = "UDP Client Hello";
    sendto(clientSocket, hello, strlen(hello), 0,
        (SOCKADDR*)&serverAddress, serverAddrSize);

    char temp_buf[MAX_BUF_SIZE + 20]{};

    int recvLen = recvfrom(clientSocket, temp_buf, MAX_BUF_SIZE + 20, 0,
        (SOCKADDR*)&serverAddress, &serverAddrSize);

    if (recvLen > 0) {
        temp_buf[recvLen] = '\0';
        cout << "서버가 보낸 내용: " << temp_buf << endl;
    }

    cout << "아이디 입력(10자 이내): ";
    getline(cin, id_str);
    if (id_str.length() > 10) {
        id_str = id_str.substr(0, 10);
    }

    while (true) {
        cout << id_str << "님(종료:exit): ";
        getline(cin, msg_str);
        if (msg_str == "exit")
            break;

        s_msg_str.clear();
        s_msg_str += "[" + id_str + "님] - " + msg_str;

        sendto(clientSocket, s_msg_str.c_str(), s_msg_str.length(), 0,
            (SOCKADDR*)&serverAddress, serverAddrSize);

        /*ZeroMemory(temp_buf, sizeof(temp_buf));

        recvLen = recvfrom(clientSocket, temp_buf, MAX_BUF_SIZE + 20, 0,
            (SOCKADDR*)&serverAddress, &serverAddrSize);

        if (recvLen > 0) {
            temp_buf[recvLen] = '\0';
            cout << "서버가 보낸 내용: " << temp_buf << endl;
        }*/
    }

	running.store(false);
    closesocket(clientSocket);
    cout << "서버와의 접속을 종료" << endl;

    WSACleanup();
    cout << "윈도우 소켓 종료" << endl;
}
