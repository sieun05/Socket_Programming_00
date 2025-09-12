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
		cout << "������ ���� �ʱ�ȭ ����" << endl;
		return 1;
	}

	SOCKET clientSocket;
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (clientSocket == INVALID_SOCKET) {
		cout << "���� ���� ����" << endl;
		WSACleanup();
		return 1;
	}

	SOCKADDR_IN serverAddress;
	ZeroMemory(&serverAddress, sizeof(serverAddress));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = inet_addr("192.168.0.63");

	if (connect(clientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) != 0) {
		cout << "���� ���ӿ� ����-IP�� PORT�� Ȯ���� ��" << endl;
		closesocket(clientSocket);
		return 1;
	}

	char msg_str[MAX_BUF_SIZE];

	while (true) {
		cout << "������ ���� ����(��ȭ����: exit): ";
		gets_s(msg_str, sizeof(msg_str));
		if (!strncmp(msg_str, "exit", sizeof(msg_str))) {
			break;
		}
		send(clientSocket, msg_str, MAX_BUF_SIZE, 0);
		ZeroMemory(msg_str, MAX_BUF_SIZE);

		recv(clientSocket, msg_str, MAX_BUF_SIZE, 0);
		cout << "������ ���� ����: " << msg_str << endl << endl;
	}

	closesocket(clientSocket);
	cout << "�������� ������ ����" << endl;

	WSACleanup();
	cout << "������ ���� ����" << endl;
}