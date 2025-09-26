#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>
#include <Windows.h>
#include "HandleClientCommand.h"
#include "Questions.h"

#pragma comment(lib, "ws2_32.lib")


#define PORT 3500
#define MAX_BUF_SIZE 256
#define FD_SETSIZE 100

using namespace std;




/*

SOCKET& client_socket
넌센스 문제에 대해 정답을 맞힌 횟수를 기록할건데, 클라이언트를 구분하는 데 필요한 데이터는 SOCKET 자료형 변수밖에 없잖아. 저 SOCKET자료형 변수를 담은 class를 따로 만들어서 데이터를 서버에서 관리하면 될까?

// ClientManager.h
#pragma once
#include <WinSock2.h>
#include <unordered_map>
#include <string>

class ClientData {
private:
    SOCKET socketID;
    int correctAnswers;
    std::string currentQuestion;  // 현재 풀고 있는 문제 저장

public:
    ClientData(SOCKET sock) : socketID(sock), correctAnswers(0) {}

    void incrementCorrectAnswers() { correctAnswers++; }
    int getCorrectAnswers() const { return correctAnswers; }
    void setCurrentQuestion(const std::string& question) { currentQuestion = question; }
    std::string getCurrentQuestion() const { return currentQuestion; }
};

class ClientManager {
private:
    std::unordered_map<SOCKET, ClientData> clients;

public:
    // 새 클라이언트 추가
    void addClient(SOCKET clientSocket) {
        clients.emplace(clientSocket, ClientData(clientSocket));
    }

    // 클라이언트 제거
    void removeClient(SOCKET clientSocket) {
        clients.erase(clientSocket);
    }

    // 정답 맞춤 처리
    void incrementScore(SOCKET clientSocket) {
        if (clients.find(clientSocket) != clients.end()) {
            clients[clientSocket].incrementCorrectAnswers();
        }
    }

    // 현재 문제 설정
    void setCurrentQuestion(SOCKET clientSocket, const std::string& question) {
        if (clients.find(clientSocket) != clients.end()) {
            clients[clientSocket].setCurrentQuestion(question);
        }
    }

    // 현재 문제 가져오기
    std::string getCurrentQuestion(SOCKET clientSocket) {
        if (clients.find(clientSocket) != clients.end()) {
            return clients[clientSocket].getCurrentQuestion();
        }
        return "";
    }

    // 점수 가져오기
    int getScore(SOCKET clientSocket) {
        if (clients.find(clientSocket) != clients.end()) {
            return clients[clientSocket].getCorrectAnswers();
        }
        return 0;
    }
};
*/