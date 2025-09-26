#include <iostream>
#include "HandleClientCommand.h"
#include "Questions.h"

using namespace std;

void SendMessageToClient(const SOCKET& clientSocket, const char* message)
{
	int send_data = send(clientSocket, message, strlen(message), 0);
	if (send_data == SOCKET_ERROR) {
		std::cerr << "�޽��� ���� ����: " << WSAGetLastError() << std::endl;
	}
}

void HandleClientCommand(const SOCKET& client_socket, const string command)
{
	std::string message;
	char str_client_socket[20];
	errno_t err = _ultoa_s(client_socket, str_client_socket, sizeof(str_client_socket), 10);

	if (err != 0) {
		cerr << "���� ��ȣ ��ȯ ����" << endl;
		return;
	}
	
	message = str_client_socket;
	message += " : ";
	
	if (command == "����") {
		Questions quiz;
		message += quiz.GetRandomQustion();
	}
	else {
		
	}

	cout << message << endl;

	SendMessageToClient(client_socket, message.c_str());
}
