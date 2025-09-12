#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 3500
#define MAX_BUF_SIZE 256
#define FD_SETSIZE 100

using namespace std;

int main() {
    WSADATA wsdata;

    if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
        cout << "윈도우 소켓 초기화 실패" << endl;
        return 1;
    }

    SOCKET serverSocket;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == INVALID_SOCKET) {
        cout << "소켓 생성 실패!" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    SOCKADDR_IN serverAddress;
    ZeroMemory(&serverAddress, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        cout << "serverSocket에 IP와 PORT를 부여하는데 실패" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "클라이언트의 접속을 대기중" << endl;
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        cout << "클라이언트의 접속 대기 실패" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    fd_set read_fds, all_fds;
    FD_ZERO(&read_fds);
    FD_SET(serverSocket, &read_fds);

    int fd_num;
    int read_data, send_data;
    SOCKET client_socket;
    int i{};
    char s_msg_str[MAX_BUF_SIZE + 20];
    char str_client_socket[10];
    char msg_str[MAX_BUF_SIZE];

    while (true) {
        all_fds = read_fds;

        fd_num = select(0, &all_fds, NULL, NULL, NULL);

        if (FD_ISSET(serverSocket, &all_fds)) {
            if ((client_socket = accept(serverSocket, NULL, NULL)) == INVALID_SOCKET) {
                cout << "클라이언트와 데이터를 주고받는 소켓을 생성할 수 없음" << endl;
                continue;
            }
            cout << client_socket << " 클라이언트 접속 성공" << endl;
            FD_SET(client_socket, &read_fds);
            continue;
        }


        for (int i{}; i < all_fds.fd_count; i++) {
            if (all_fds.fd_array[i] == serverSocket) continue;
            client_socket = all_fds.fd_array[i];
            ZeroMemory(msg_str, MAX_BUF_SIZE);
            read_data = recv(client_socket, msg_str, MAX_BUF_SIZE, 0);

            if (read_data <= 0) {
                closesocket(client_socket);
                FD_CLR(client_socket, &read_fds);
                cout << client_socket << " 클라이언트 접속 종료" << endl;
            }
            else {
                cout << client_socket << " 클라이언트가 보낸 메세지: " << msg_str << endl;
                _ultoa(client_socket, str_client_socket, 10);
                ZeroMemory(s_msg_str, MAX_BUF_SIZE + 20);
                strcat(s_msg_str, str_client_socket);
                strcat(s_msg_str, ",");
                strcat(s_msg_str, msg_str);
                send_data = send(client_socket, s_msg_str, strlen(s_msg_str), 0);
            }
        }
    }

    closesocket(client_socket);
    cout << "클라이언트와의 접속을 종료" << endl;
    closesocket(serverSocket);
    cout << "serverSocket 닫음" << endl;

    WSACleanup();
    cout << "윈도우 소켓 종료" << endl;
}