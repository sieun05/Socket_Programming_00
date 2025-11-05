//251015 소켓 숫자데이터 전송
#include "헤더.h"
#include "HandleClientCommand.h"
#include "Data.h"

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
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		cout << "serverSocket에 IP와 PORT를 부여하는데 실패" << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}

	cout << "클라이언트의 접속을 대기중" << endl;
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		cout << "클라이언트의 접속 대기 실패" << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}

	fd_set read_fds, all_fds;
	FD_ZERO(&read_fds);
	FD_SET(serverSocket, &read_fds);


	int fd_num;
	int read_data, send_data;
	SOCKET client_socket;

	Data msg_data;

	while (true) {
		all_fds = read_fds;

		fd_num = select(0, &all_fds, NULL, NULL, NULL);

		if (FD_ISSET(serverSocket, &all_fds)) {
			if ((client_socket = accept(serverSocket, NULL, NULL)) == INVALID_SOCKET) {
				cout << "클라이언트와 데이터를 주고받는 소켓을 생성할 수 없음" << endl;
				continue;
			}
			cout << client_socket << " 클라이언트 접속 성공" << endl;
			FD_SET(client_socket, &read_fds);
			continue;
		}


		for (int i{}; i < all_fds.fd_count; i++) {
			if (all_fds.fd_array[i] == serverSocket) continue;
			client_socket = all_fds.fd_array[i];

			ZeroMemory(&msg_data, sizeof(msg_data));

			read_data = recv(client_socket, (char*)&msg_data, sizeof(msg_data), 0);


			if (read_data <= 0) {
				closesocket(client_socket);
				FD_CLR(client_socket, &read_fds);
				cout << client_socket << " 클라이언트 접속 종료" << endl;
			}
			else {
				msg_data.x = ntohl(msg_data.x);
				msg_data.y = ntohl(msg_data.y);
				cout << client_socket << " 클라이언트가 보낸 메세지: " << msg_data.msg_str << ", " << msg_data.x << ", " << msg_data.y << endl;

				HandleClientCommand_ex8(client_socket, msg_data, sizeof(msg_data));
			}
		}
	}

	closesocket(client_socket);
	cout << "클라이언트와의 접속을 종료" << endl;
	closesocket(serverSocket);
	cout << "serverSocket 닫음" << endl;

	WSACleanup();
	cout << "윈도우 소켓 종료" << endl;

}