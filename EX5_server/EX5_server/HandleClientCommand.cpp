#include <iostream>
#include "HandleClientCommand.h"


using namespace std;

ClientManager clientManager;

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


void SendMessageToClient_test(const SOCKET& clientSocket, test_Data data, int size)
{
	data.score = htonl(data.score);

	int send_data = send(clientSocket, (char*)&data, size, 0);
	if (send_data == SOCKET_ERROR) {
		std::cerr << "메시지 전송 실패: " << WSAGetLastError() << std::endl;
	}
}

void HandleClientCommand_test(const SOCKET& clientSocket, test_Data data, int size)
{
	data.score = ntohl(data.score);
	cout << clientSocket << " 클라이언트가 보낸 메세지" << endl;
	cout << data << endl;

	if (clientManager.isInQuiz(clientSocket)) {
		clientManager.setInQuiz(clientSocket, false);
		data.quiz_flag = false;
		int cnt{};

		Questions questions;
		for (int i{}; i < 10; i++) {
			if (questions.CheckAnswer(data.answers[i], data.questions[i])) {
				clientManager.incrementScore(clientSocket);
				cnt++;
			}
		}

		data.score = clientManager.getScore(clientSocket);
		data.answers[0] = "퀴즈 종료! 맞춘 개수: " + std::to_string(cnt) + " / 10";
	}
	else {
		if (data.answers[0] == "문제") {
			clientManager.setInQuiz(clientSocket, true);

			Questions questions;
			std::string quiz_questions[10];
			for (int i{}; i < 10; i++) {
				quiz_questions[i] = questions.GetRandomQustion();
				if (quiz_questions->find(quiz_questions[i]) != std::string::npos) {
					i--;
				}
			}
			clientManager.setCurrentQuestions(clientSocket, quiz_questions);
			for (int i{}; i < 10; i++) {
				data.questions[i] = quiz_questions[i];
			}
			data.quiz_flag = true;
			data.score = clientManager.getScore(clientSocket);

			data.questions[0] = "퀴즈 시작! 총 10문제입니다.";
		}
		else {
			data.questions[0] = data.answers[0] + " - 회신됨";
		}
	}

	SendMessageToClient_test(clientSocket, data, size);
}
