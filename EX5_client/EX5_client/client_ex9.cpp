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

	Data data[3];

	while (true) {
		ZeroMemory(&data, sizeof(data));

		cout << "서버에 보낼 내용(대화종료: 999): " << endl;

		for (int i{}; i < 3; i++) {
			cout << i << "번째 " << "Data 문자열 입력: ";
			cin.getline(data[i].msg_str, MAX_BUF_SIZE, '\n');
			cout << i << "번째 " << "Data x 입력: ";
			cin >> data[i].x;
			cout << i << "번째 " << "Data y 입력: ";
			cin >> data[i].y;

			cin.clear();
			cin.ignore(MAX_BUF_SIZE, '\n');
		}
		

		if (not (strcmp(data[0].msg_str, "999") or strcmp(data[1].msg_str, "999") or strcmp(data[2].msg_str, "999"))) {
			cout << "대화 종료" << endl;
			break;
		}

		cout << data[0].x << endl;

		for (int i{}; i < 3; i++)
		{
			data[i].x = htonl(data[i].x);
			data[i].y = htonl(data[i].y);
		}
		
		cout << data[0].x << endl;

		send(clientSocket, (char*)data, sizeof(data), 0);

		ZeroMemory(&data, sizeof(data));
		recv(clientSocket, (char*)data, sizeof(data), 0);

		cout << data[0].x << endl;

		for (int i{}; i < 3; i++)
		{
			data[i].x = ntohl(data[i].x);
			data[i].y = ntohl(data[i].y);
		}

		cout << data[0].x << endl;

		cout << "서버가 보낸 내용: " << endl;

		for (int i{}; i < 3; i++)
			cout << i << "번째 " << "Data 문자열: " << data[i].msg_str << ", x: " << data[i].x << ", y: " << data[i].y << endl;

		
	}

	closesocket(clientSocket);
	cout << "서버와의 접속을 종료" << endl;

	WSACleanup();
	cout << "윈도우 소켓 종료" << endl;
}