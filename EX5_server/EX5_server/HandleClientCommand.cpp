#include <iostream>
#include "HandleClientCommand.h"

using namespace std;

void SendMessageToClient(const SOCKET& clientSocket, int message[])
{
	cout << ntohl(message[2]);
	int send_data = send(clientSocket, (char*)message, sizeof(message), 0);
	if (send_data == SOCKET_ERROR) {
		std::cerr << "메시지 전송 실패: " << WSAGetLastError() << std::endl;
	}
}

void HandleClientCommand(const SOCKET& clientSocket, int command[])
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
	cout << clientSocket << " 클라이언트가 보낸 메세지: " << command[0] << ", " << command[1] << ", " << command[2] << endl;
	for (int i{}; i < 3; i++) {
		command[i] = htonl(command[i]);
	}
	
	SendMessageToClient(clientSocket, command);
}
