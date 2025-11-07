#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <iostream>
#include <Windows.h>
#include <string>

#include "test_Data.h"

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

	test_Data data;

	while (true) {
		ZeroMemory(&data, sizeof(data));

		if (data.quiz_flag) {
			cout << "- 문제 풀기 (현재 점수: " << data.score << ") -" << endl;
			for (int i{}; i < 10; i++) {
				cout << i+1 << "번째 문제: " << data.questions[i] << endl;

				cout << "답: ";
				cin >> data.answers[i];

				cin.clear();
				cin.ignore(MAX_BUF_SIZE, '\n');
			}
		}
		else {
			cout << "서버에 보낼 내용(\"문제\": 10개문제풀기/대화종료: 999): " << endl;
			cin >> data.answers[0];

			if (data.answers[0] == "999") {
				cout << "대화 종료" << endl;
				break;
			}

			cin.clear();
			cin.ignore(MAX_BUF_SIZE, '\n');
		}

		data.score = htonl(data.score);

		send(clientSocket, (char*)&data, sizeof(data), 0);

		ZeroMemory(&data, sizeof(data));
		recv(clientSocket, (char*)&data, sizeof(data), 0);

		cout << "서버가 보낸 내용: " << endl;

		cout << data.questions[0] << " / score: " << ntohl(data.score) << endl;
	}

	closesocket(clientSocket);
	cout << "서버와의 접속을 종료" << endl;

	WSACleanup();
	cout << "윈도우 소켓 종료" << endl;
}