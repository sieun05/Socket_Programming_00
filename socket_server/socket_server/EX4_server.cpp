//4�ܿ� ����: ��Ģ���� ���� �Ǵ� �ͼ��� ��� ������. 
//Ŭ���̾�Ʈ���� ���� ��û�ϸ� ������ ����Ѵ�.
//10������ Ǯ���ϸ� Ŭ���̾�Ʈ ���� �Ǵܿ� ���� ��, Ʋ�� ��, ����, Ǯ�̽ð� ����� �� (�� cpp���� ���� �ϱ�)

#include "head.h"

extern ClientManager clientManager;

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
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		cout << "serverSocket�� IP�� PORT�� �ο��ϴµ� ����" << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}

	cout << "Ŭ���̾�Ʈ�� ������ �����" << endl;
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		cout << "Ŭ���̾�Ʈ�� ���� ��� ����" << endl;
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
				cout << "Ŭ���̾�Ʈ�� �����͸� �ְ�޴� ������ ������ �� ����" << endl;
				continue;
			}
			cout << client_socket << " Ŭ���̾�Ʈ ���� ����" << endl;
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
				cout << client_socket << " Ŭ���̾�Ʈ ���� ����" << endl;
				clientManager.removeClient(client_socket);
			}
			else {
				cout << client_socket << " Ŭ���̾�Ʈ�� ���� �޼���: " << msg_str << endl;
				HandleClientCommand(client_socket, msg_str);
			}
		}
	}

	closesocket(client_socket);
	cout << "Ŭ���̾�Ʈ���� ������ ����" << endl;
	closesocket(serverSocket);
	cout << "serverSocket ����" << endl;

	WSACleanup();
	cout << "������ ���� ����" << endl;

}