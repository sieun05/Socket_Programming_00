//4단원 예제: 사칙연산 퀴즈 또는 넌센스 퀴즈를 만들어보라. 
//클라이언트에서 문제 요청하면 문제를 출력한다.
//10문제를 풀이하면 클라이언트 최종 판단에 맞은 수, 틀린 수, 점수, 풀이시간 출력할 것 (새 cpp파일 만들어서 하기)

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
		cout << "소켓 생성 실패" << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}

	SOCKADDR_IN serverAddress;
	ZeroMemory(&serverAddress, sizeof(serverAddress));

	serverAddress.sin_family = AF_INET;
}