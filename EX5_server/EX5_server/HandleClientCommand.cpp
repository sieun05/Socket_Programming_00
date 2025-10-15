#include <iostream>
#include "HandleClientCommand.h"

using namespace std;

void SendMessageToClient(const SOCKET& clientSocket, int message[])
{
	cout << ntohl(message[2]);
	int send_data = send(clientSocket, (char*)message, sizeof(message), 0);
	if (send_data == SOCKET_ERROR) {
		std::cerr << "�޽��� ���� ����: " << WSAGetLastError() << std::endl;
	}
}

void HandleClientCommand(const SOCKET& clientSocket, int command[])
{

	//std::string message;
	//char str_client_socket[20];
	//errno_t err = _ultoa_s(clientSocket, str_client_socket, sizeof(str_client_socket), 10);

	//if (err != 0) {
	//	cerr << "���� ��ȣ ��ȯ ����" << endl;
	//	return;
	//}

	//message = str_client_socket;
	//message += " :: ";
	cout << clientSocket << " Ŭ���̾�Ʈ�� ���� �޼���: " << command[0] << ", " << command[1] << ", " << command[2] << endl;
	for (int i{}; i < 3; i++) {
		command[i] = htonl(command[i]);
	}
	
	SendMessageToClient(clientSocket, command);
}
