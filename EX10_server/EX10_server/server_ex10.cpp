//251015 소켓 숫자데이터 전송
#include "헤더.h"
#include "HandleClientCommand.h"

int client_s_num[MAX_CLIENT] = { 0, };
int num_client = 0;
int maxfdp1;

int getmax(int k) {
	int max = k;
	for (int i{}; i < num_client; i++) {
		if (client_s_num[i] > max) {
			max = client_s_num[i];
		}
	}
	return max;
}

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

	maxfdp1 = serverSocket + 1;

	fd_set read_fds;

	int fd_num;
	int read_data, send_data;
	SOCKET client_socket;

	//char s_msg_str[MAX_BUF_SIZE + 20];
	//char str_client_socket[10];
	std::string s_msg_str{};
	//std::string str_client_socket{};

	while (true) {
		FD_ZERO(&read_fds);
		FD_SET(serverSocket, &read_fds);
		for (int i{}; i < num_client; i++) {
			FD_SET(client_s_num[i], &read_fds);
		}
		maxfdp1 = getmax(serverSocket) + 1;

		fd_num = select(maxfdp1, &read_fds, NULL, NULL, NULL);
		if (fd_num < 0) {
			cout << "select 함수 오류" << endl;
			break;
		}

		if (FD_ISSET(serverSocket, &read_fds)) {
			if ((client_socket = accept(serverSocket, NULL, NULL)) == INVALID_SOCKET) {
				cout << "클라이언트와 데이터를 주고받는 소켓을 생성할 수 없음" << endl;
				continue;
			}
			cout << client_socket << " 클라이언트 접속 성공" << endl;
			s_msg_str.clear();
			s_msg_str += std::to_string(client_socket) + "님이 접속하였습니다.";;
			send(client_socket, s_msg_str.c_str(), s_msg_str.length(), 0);
			client_s_num[num_client] = client_socket;
			num_client++;
			continue;
		}


		for (int i{}; i < num_client; i++) {
			if (FD_ISSET(client_s_num[i], &read_fds)) {
				s_msg_str.clear();
				char temp_buf[MAX_BUF_SIZE + 20]{};
				read_data = recv(client_s_num[i], temp_buf, MAX_BUF_SIZE + 20, 0);
				s_msg_str += std::to_string(client_s_num[i]) + ": " + temp_buf;
				if (read_data <= 0) {
					closesocket(client_s_num[i]);
					FD_CLR(client_s_num[i], &read_fds);
					cout << client_s_num[i] << " 클라이언트 접속 종료" << endl;
					if (i != num_client - 1) {
						client_s_num[i] = client_s_num[num_client - 1];
					}
					num_client--;
					cout << "채팅 참가자 1명 감소. 현재 참가자 수: " << num_client << endl;
				}
				else {
					for (int j{}; j < num_client; j++) {
						if (i == j) continue;		//자기 자신에게는 송신하지 않음

						send_data = send(client_s_num[i], s_msg_str.c_str(),s_msg_str.length(), 0);
						cout << "클라이언트로 데이터 전송: " << s_msg_str << endl;
					}
				}
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