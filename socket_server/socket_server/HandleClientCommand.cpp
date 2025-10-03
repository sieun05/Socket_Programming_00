#include <iostream>
#include "HandleClientCommand.h"
#include "Questions.h"
#include "ClientManager.h"

using namespace std;

ClientManager clientManager;

void SendMessageToClient(const SOCKET& clientSocket, const char* message)
{
	int send_data = send(clientSocket, message, strlen(message), 0);
	if (send_data == SOCKET_ERROR) {
		std::cerr << "메시지 전송 실패: " << WSAGetLastError() << std::endl;
	}
}

void HandleClientCommand(const SOCKET& client_socket, const string command)
{
	std::string message;
	char str_client_socket[20];
	errno_t err = _ultoa_s(client_socket, str_client_socket, sizeof(str_client_socket), 10);

	if (err != 0) {
		cerr << "소켓 번호 변환 실패" << endl;
		return;
	}
	
	message = str_client_socket;
	message += " :: ";
	
	if (not clientManager.isInQuiz(client_socket)) {
		if (command == "문제") {
			Questions quiz;
			std::string question = quiz.GetRandomQustion();
			clientManager.setCurrentQudstion(client_socket, question);
			message += question;
			clientManager.setInQuiz(client_socket, true);
		}
		else {
			message += "퀴즈를 시작하려면 '문제'를 입력하세요.";
		}
	}
	else {
		//문제 요청
		if (command == "문제확인")
		{
			message += clientManager.getCurrentQuestion(client_socket);
		}
		else {
			//답변 체크
			clientManager.incrementQuizCnt(client_socket);

			std::string currentQuestion = clientManager.getCurrentQuestion(client_socket);
			Questions quiz;
			if (quiz.CheckAnswer(currentQuestion, command)) {
				message += "정답.\n";
				clientManager.incrementScore(client_socket);
			}
			else {
				message += "오답\n";
			}

			if (clientManager.getQuizCnt(client_socket) >= 10) {
				message += "10문제 모두 풀었습니다.\n";
				message += "맞은 개수: " + std::to_string(clientManager.getScore(client_socket)) + "\n";
				message += "틀린 개수: " + std::to_string(10 - clientManager.getScore(client_socket)) + "\n";
				clientManager.resetClient(client_socket);
			}
			else {
				std::string question = quiz.GetRandomQustion();
				clientManager.setCurrentQudstion(client_socket, question);
				message += "다음문제: " + question;
			}
		}
	}

	cout << message << endl;
	SendMessageToClient(client_socket, message.c_str());
}
