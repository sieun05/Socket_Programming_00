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


	int num[3]{};

	while (true) {
		cout << "������ ���� ����(��ȭ����: exit): " << endl;

		for (int i{}; i < 3; i++) {
			cout << i << "��° int ������ �Է�: ";
			cin >> num[i];

			if (cin.fail()) {
				cout << "������ �����Ͱ� �ƴ�. ����" << endl;
				i--;
				continue;
			}
			if (num[i] == 999) break;
		
			cout << endl;
		}
		
		if (num[0] == 999 || num[1] == 999 || num[2] == 999) {
			cout << "��ȭ ����" << endl;
			break;
		}

		for (int i{}; i < 3; i++) {
			num[i] = htonl(num[i]);
		}
		send(clientSocket, (char*)&num, sizeof(num), 0);

		for (int i{}; i < 3; i++) {
			num[i] = 0;
		}

		//�� ��° ���� �� ���� why???

		recv(clientSocket, (char*)&num, sizeof(num), 0);
		cout << "������ ���� ����: " << num[0] << ", " << num[1] << ", " << num[2] << endl << endl;

		for (int i{}; i < 3; i++) {
			num[i] = ntohl(num[i]);
		}

		cout << "������ ���� ����: " << num[0] << ", " << num[1] << ", " << num[2] << endl << endl;
	}

	closesocket(clientSocket);
	cout << "�������� ������ ����" << endl;

	WSACleanup();
	cout << "������ ���� ����" << endl;
}