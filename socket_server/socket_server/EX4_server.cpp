//4�ܿ� ����: ��Ģ���� ���� �Ǵ� �ͼ��� ��� ������. 
//Ŭ���̾�Ʈ���� ���� ��û�ϸ� ������ ����Ѵ�.
//10������ Ǯ���ϸ� Ŭ���̾�Ʈ ���� �Ǵܿ� ���� ��, Ʋ�� ��, ����, Ǯ�̽ð� ����� �� (�� cpp���� ���� �ϱ�)

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
		cout << "������ ���� �ʱ�ȭ ����" << endl;
		return 1;
	}

	SOCKET serverSocket;
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (serverSocket == INVALID_SOCKET) {
		cout << "���� ���� ����" << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}

	SOCKADDR_IN serverAddress;
	ZeroMemory(&serverAddress, sizeof(serverAddress));

	serverAddress.sin_family = AF_INET;
}