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


	int num{};

	while (true) {
		cout << "������ ���� ����(��ȭ����: exit): ";

		cin >> num;
		if (num == 999) break;
		num = htonl(num);

		send(clientSocket, (char*)&num, sizeof(num), 0);

		num = 0;
		recv(clientSocket, (char*)&num, sizeof(num), 0);
		num = ntohl(num);

		cout << "������ ���� ����: " << num << endl << endl;
	}

	closesocket(clientSocket);
	cout << "�������� ������ ����" << endl;

	WSACleanup();
	cout << "������ ���� ����" << endl;
}