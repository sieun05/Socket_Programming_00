#define _WINSOCK_DEPRECATED_NO_WARNINGS

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

	char msg_str[3][MAX_BUF_SIZE]{};

	while (true) {
		cout << "서버에 보낼 내용(대화종료: exit): " << endl;

		for (int i{}; i < 3; i++) {
			cout << i << "번째 문자열 데이터 입력: ";
			cin.clear();
			cin.getline(msg_str[i], MAX_BUF_SIZE, '\n');
			
			if (not strcmp(msg_str[i], "999"))	break;

			cout << endl;
		}

		if (not (strcmp(msg_str[0], "999") or strcmp(msg_str[1], "999") or strcmp(msg_str[2], "999"))) {
			cout << "대화 종료" << endl;
			break;
		}

		send(clientSocket, (char*)msg_str, sizeof(msg_str), 0);

		ZeroMemory(&msg_str, sizeof(msg_str));
		cout << sizeof(msg_str) << endl;
		recv(clientSocket, (char*)msg_str, sizeof(msg_str), 0);
		cout << "서버가 보낸 내용: " << msg_str[0] << ", " << msg_str[1] << ", " << msg_str[2] << endl << endl;

	}

	closesocket(clientSocket);
	cout << "서버와의 접속을 종료" << endl;

	WSACleanup();
	cout << "윈도우 소켓 종료" << endl;
}