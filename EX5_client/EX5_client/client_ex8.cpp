#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <iostream>
#include <Windows.h>
//#include <string>

#include "Data.h"

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

	Data data;

	while (true) {
		ZeroMemory(&data, sizeof(data));

		cout << "서버에 보낼 내용(대화종료: 999): " << endl;

		cout << "Data 문자열 입력: ";
		cin.getline(data.msg_str, MAX_BUF_SIZE, '\n');
		cout << "Data x 입력: ";
		cin >> data.x;
		cout << "Data y 입력: ";
		cin >> data.y;

		if (not (strcmp(data.msg_str, "999"))) {
			cout << "대화 종료" << endl;
			break;
		}


		data.x = htonl(data.x);
		data.y = htonl(data.y);
		send(clientSocket, (char*)&data, sizeof(data), 0);

		ZeroMemory(&data, sizeof(data));
		recv(clientSocket, (char*)&data, sizeof(data), 0);

		data.x = ntohl(data.x);
		data.y = ntohl(data.y);
		cout << "서버가 보낸 내용: " << data.msg_str << ", " << data.x << ", " << data.y << endl << endl;

	}

	closesocket(clientSocket);
	cout << "서버와의 접속을 종료" << endl;

	WSACleanup();
	cout << "윈도우 소켓 종료" << endl;
}