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
	message += " :: ";
	
	if (not clientManager.isInQuiz(client_socket)) {
		if (command == "����") {
			Questions quiz;
			std::string question = quiz.GetRandomQustion();
			clientManager.setCurrentQudstion(client_socket, question);
			message += question;
			clientManager.setInQuiz(client_socket, true);
		}
		else {
			message += "��� �����Ϸ��� '����'�� �Է��ϼ���.";
		}
	}
	else {
		//���� ��û
		if (command == "����Ȯ��")
		{
			message += clientManager.getCurrentQuestion(client_socket);
		}
		else {
			//�亯 üũ
			clientManager.incrementQuizCnt(client_socket);

			std::string currentQuestion = clientManager.getCurrentQuestion(client_socket);
			Questions quiz;
			if (quiz.CheckAnswer(currentQuestion, command)) {
				message += "����.\n";
				clientManager.incrementScore(client_socket);
			}
			else {
				message += "����\n";
			}

			if (clientManager.getQuizCnt(client_socket) >= 10) {
				message += "10���� ��� Ǯ�����ϴ�.\n";
				message += "���� ����: " + std::to_string(clientManager.getScore(client_socket)) + "\n";
				message += "Ʋ�� ����: " + std::to_string(10 - clientManager.getScore(client_socket)) + "\n";
				clientManager.resetClient(client_socket);
			}
			else {
				std::string question = quiz.GetRandomQustion();
				clientManager.setCurrentQudstion(client_socket, question);
				message += "��������: " + question;
			}
		}
	}

	cout << message << endl;
	SendMessageToClient(client_socket, message.c_str());
}
