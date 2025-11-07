#pragma once
#include <WinSock2.h>
#include <string>
#include <unordered_map>

using namespace std;

class ClientData {
private:
	SOCKET socketID{};
	int score{};
	int quiz_cnt{};
	std::string currentQuestions[10]{};
	bool quiz_flag{};

public:
	ClientData() = default;
	ClientData(const SOCKET& socket) : socketID{ socket }, score{ 0 }, quiz_cnt{ 0 }, quiz_flag{ false } {}
	ClientData(const ClientData& other) = default;
	ClientData& operator=(const ClientData& other) = default;

	void increamCorrentAnswers() { score++; }
	void increamCorrentAnswers(int num) { score += num; }
	int getScore() const { return score; }

	/*void setCurrentQuestion(const std::string& question) { currentQuestion = question; }
	std::string getCurrentQuestion() const { return currentQuestions; }*/
	void setCurrentQuestions(const std::string questions[]) { 
		for (int i{}; i < 10; i++) {
			currentQuestions[i] = questions[i];
		}
	}

	int getQuizCnt() const { return quiz_cnt; }
	void incrementQuizCnt() { quiz_cnt++; }

	bool isInQuiz() const { return quiz_flag; }
	void setInQuiz(bool flag) { quiz_flag = flag; }
};

class ClientManager {
private:
	std::unordered_map<SOCKET, ClientData> clients;

public:
	void addClient(const SOCKET& clientSocket) {
		clients.emplace(clientSocket, ClientData(clientSocket));
	}

	void removeClient(const SOCKET& clientSocket) {
		clients.erase(clientSocket);
	}

	//정답 맞춤 처리
	void incrementScore(const SOCKET& clientSocket) {
		if (clients.find(clientSocket) != clients.end()) {
			clients[clientSocket].increamCorrentAnswers();
		}
	}

	//void setCurrentQudstion(const SOCKET& clientSocket, const std::string& question) {
	//	if (clients.find(clientSocket) != clients.end()) {
	//		clients[clientSocket].setCurrentQuestion(question);
	//	}
	//}

	void setCurrentQuestions(const SOCKET& clientSocket, const std::string* questions)
	{
		if (clients.find(clientSocket) != clients.end()) {
			clients[clientSocket].setCurrentQuestions(questions);
		}
	}

	//std::string getCurrentQuestion(const SOCKET& clientSocket) {
	//	if (clients.find(clientSocket) != clients.end()) {
	//		return clients[clientSocket].getCurrentQuestion();
	//	}
	//	return "";
	//}

	int getScore(const SOCKET& clientSocket) {
		if (clients.find(clientSocket) != clients.end()) {
			return clients[clientSocket].getScore();
		}
		return 0;
	}

	int getQuizCnt(const SOCKET& clientSocket) {
		if (clients.find(clientSocket) != clients.end()) {
			return clients[clientSocket].getQuizCnt();
		}
		return 0;
	}

	void incrementQuizCnt(const SOCKET& clientSocket) {
		if (clients.find(clientSocket) != clients.end()) {
			clients[clientSocket].incrementQuizCnt();
		}
	}

	void resetClient(const SOCKET& clientSocket) {
		if (clients.find(clientSocket) != clients.end()) {
			clients[clientSocket] = ClientData(clientSocket);
		}
	}

	bool isInQuiz(const SOCKET& clientSocket) {
		if (clients.find(clientSocket) != clients.end()) {
			return clients[clientSocket].isInQuiz();
		}
		return false;
	}

	void setInQuiz(const SOCKET& clientSocket, bool flag) {
		if (clients.find(clientSocket) != clients.end()) {
			clients[clientSocket].setInQuiz(flag);
		}
	}
};