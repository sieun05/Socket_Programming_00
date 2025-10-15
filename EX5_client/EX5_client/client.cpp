#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <iostream>
#include <Windows.h>

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


	int num[3]{};

	while (true) {
		cout << "서버에 보낼 내용(대화종료: exit): " << endl;

		for (int i{}; i < 3; i++) {
			cout << i << "번째 int 데이터 입력: ";
			cin >> num[i];

			if (cin.fail()) {
				cout << "정수형 데이터가 아님. 종료" << endl;
				i--;
				continue;
			}
			if (num[i] == 999) break;
		
			cout << endl;
		}
		
		if (num[0] == 999 || num[1] == 999 || num[2] == 999) {
			cout << "대화 종료" << endl;
			break;
		}

		for (int i{}; i < 3; i++) {
			num[i] = htonl(num[i]);
		}
		send(clientSocket, (char*)&num, sizeof(num), 0);

		for (int i{}; i < 3; i++) {
			num[i] = 0;
		}

		//세 번째 값을 안 받음 why???
		cout << sizeof(num) << ' ' << sizeof(num[0]) << endl;

		recv(clientSocket, (char*)&num, sizeof(num), 0);
		cout << "서버가 보낸 내용: " << num[0] << ", " << num[1] << ", " << num[2] << endl << endl;

		for (int i{}; i < 3; i++) {
			num[i] = ntohl(num[i]);
		}

		cout << "서버가 보낸 내용: " << num[0] << ", " << num[1] << ", " << num[2] << endl << endl;
	}

	closesocket(clientSocket);
	cout << "서버와의 접속을 종료" << endl;

	WSACleanup();
	cout << "윈도우 소켓 종료" << endl;
}