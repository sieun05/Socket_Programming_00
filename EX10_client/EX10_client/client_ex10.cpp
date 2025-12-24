#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <winsock2.h>
#include <iostream>
#include <Windows.h>
//#include <string>

#pragma comment(lib, "ws2_32.lib");

#define PORT 3500
#define MAX_BUF_SIZE 256

using namespace std;

int main() {
	WSADATA wsdata;

	if (WSAStartup(MAKEWORD(2, 2), &wsdata) != 0) {
		cout << "윈도우 소켓 초기화 실패" << endl;
		return 1;
	}

	SOCKET clientSocket;
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (clientSocket == INVALID_SOCKET) {
		cout << "소켓 생성 실패" << endl;
		WSACleanup();
		return 1;
	}

	SOCKADDR_IN serverAddress;
	ZeroMemory(&serverAddress, sizeof(serverAddress));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = inet_addr("192.168.0.63");

	if (connect(clientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) != 0) {
		cout << "서버 접속에 실패-IP와 PORT를 확인할 것" << endl;
		closesocket(clientSocket);
		return 1;
	}

	char msg_str[MAX_BUF_SIZE];
	char id_str[10];
	char s_msg_str[MAX_BUF_SIZE + 20];

	ZeroMemory(s_msg_str, MAX_BUF_SIZE + 20);
	recv(clientSocket, s_msg_str, MAX_BUF_SIZE + 20, 0);
	cout << "서버가 보낸 내용: " << s_msg_str << endl;
	cout << "아이디 입력(10자 이내): ";
	cin.getline(id_str, 10, '\n');


	while (true) {
		cout << id_str << "남(종료:exit): ";
		cin.getline(msg_str, MAX_BUF_SIZE, '\n');
		if (!strcmp(msg_str, "exit"))
			break;
		ZeroMemory(s_msg_str, MAX_BUF_SIZE + 20);
		strcat(s_msg_str, "[ ");
		strcat(s_msg_str, id_str);
		strcat(s_msg_str, "님] - ");
		strcat(s_msg_str, msg_str);

		send(clientSocket, s_msg_str, strlen(s_msg_str) + 1, 0);
		ZeroMemory(s_msg_str, MAX_BUF_SIZE + 20);
		recv(clientSocket, s_msg_str, MAX_BUF_SIZE + 20, 0);
		cout << "서버가 보낸 내용: " << s_msg_str << endl;
	}


	closesocket(clientSocket);
	cout << "서버와의 접속을 종료" << endl;

	WSACleanup();
	cout << "윈도우 소켓 종료" << endl;
}