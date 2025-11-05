#include <iostream>
#include "HandleClientCommand.h"

using namespace std;

void SendMessageToClient(const SOCKET& clientSocket, int message[3], int size)
{
	int send_data = send(clientSocket, (char*)message, size, 0);
	if (send_data == SOCKET_ERROR) {
		std::cerr << "메시지 전송 실패: " << WSAGetLastError() << std::endl;
	}
}

void HandleClientCommand(const SOCKET& clientSocket, int command[3], int size)
{

	//std::string message;
	//char str_client_socket[20];
	//errno_t err = _ultoa_s(clientSocket, str_client_socket, sizeof(str_client_socket), 10);

	//if (err != 0) {
	//	cerr << "소켓 번호 변환 실패" << endl;
	//	return;
	//}

	//message = str_client_socket;
	//message += " :: ";

	for (int i{}; i < 3; i++) {
		command[i] = htonl(command[i]+100);
	}
	
	SendMessageToClient(clientSocket, command, size);
}


void SendMessageToClient_ex7(const SOCKET& clientSocket, char message[][MAX_BUF_SIZE], int size)
{
	cout << size << " " << MAX_BUF_SIZE << " " << size * MAX_BUF_SIZE << endl;

	int send_data = send(clientSocket, (char*)message, size*MAX_BUF_SIZE, 0);
	if (send_data == SOCKET_ERROR) {
		std::cerr << "메시지 전송 실패: " << WSAGetLastError() << std::endl;
	}
}

void HandleClientCommand_ex7(const SOCKET& clientSocket, char command[][MAX_BUF_SIZE], int size)
{

	SendMessageToClient_ex7(clientSocket, command, size);
}



void SendMessageToClient_ex8(const SOCKET& clientSocket, Data data, int size)
{

	int send_data = send(clientSocket, (char*)&data, size, 0);
	if (send_data == SOCKET_ERROR) {
		std::cerr << "메시지 전송 실패: " << WSAGetLastError() << std::endl;
	}
}

void HandleClientCommand_ex8(const SOCKET& clientSocket, Data data, int size)
{

	data.x = htonl(data.x);
	data.y = htonl(data.y);

	SendMessageToClient_ex8(clientSocket, data, size);
}


void SendMessageToClient_ex9(const SOCKET& clientSocket, Data data[], int size)
{

	int send_data = send(clientSocket, (char*)data, size, 0);
	if (send_data == SOCKET_ERROR) {
		std::cerr << "메시지 전송 실패: " << WSAGetLastError() << std::endl;
	}
}

void HandleClientCommand_ex9(const SOCKET& clientSocket, Data data[], int size)
{

	for (int i{}; i < size / sizeof(Data); i++) {
		data[i].x = htonl(data[i].x);
		data[i].y = htonl(data[i].y);
	}

	SendMessageToClient_ex9(clientSocket, data, size);
}
