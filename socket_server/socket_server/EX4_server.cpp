//4단원 예제: 사칙연산 퀴즈 또는 넌센스 퀴즈를 만들어보라. 
//클라이언트에서 문제 요청하면 문제를 출력한다.
//10문제를 풀이하면 클라이언트 최종 판단에 맞은 수, 틀린 수, 점수, 풀이시간 출력할 것 (새 cpp파일 만들어서 하기)

#include "head.h"

extern ClientManager clientManager;

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
	int i{};
	char msg_str[MAX_BUF_SIZE];

	while (true) {
		all_fds = read_fds;

		fd_num = select(0, &all_fds, NULL, NULL, NULL);

		if (FD_ISSET(serverSocket, &all_fds)) {
			if ((client_socket = accept(serverSocket, NULL, NULL)) == INVALID_SOCKET) {
				cout << "클라이언트와 데이터를 주고받는 소켓을 생성할 수 없음" << endl;
				continue;
			}
			cout << client_socket << " 클라이언트 접속 성공" << endl;
			clientManager.addClient(client_socket);
			FD_SET(client_socket, &read_fds);
			continue;
		}


		for (int i{}; i < all_fds.fd_count; i++) {
			if (all_fds.fd_array[i] == serverSocket) continue;
			client_socket = all_fds.fd_array[i];
			ZeroMemory(msg_str, MAX_BUF_SIZE);
			read_data = recv(client_socket, msg_str, MAX_BUF_SIZE, 0);

			if (read_data <= 0) {
				closesocket(client_socket);
				FD_CLR(client_socket, &read_fds);
				cout << client_socket << " 클라이언트 접속 종료" << endl;
				clientManager.removeClient(client_socket);
			}
			else {
				cout << client_socket << " 클라이언트가 보낸 메세지: " << msg_str << endl;
				HandleClientCommand(client_socket, msg_str);
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