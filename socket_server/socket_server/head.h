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
�ͼ��� ������ ���� ������ ���� Ƚ���� ����Ұǵ�, Ŭ���̾�Ʈ�� �����ϴ� �� �ʿ��� �����ʹ� SOCKET �ڷ��� �����ۿ� ���ݾ�. �� SOCKET�ڷ��� ������ ���� class�� ���� ���� �����͸� �������� �����ϸ� �ɱ�?

// ClientManager.h
#pragma once
#include <WinSock2.h>
#include <unordered_map>
#include <string>

class ClientData {
private:
    SOCKET socketID;
    int correctAnswers;
    std::string currentQuestion;  // ���� Ǯ�� �ִ� ���� ����

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
    // �� Ŭ���̾�Ʈ �߰�
    void addClient(SOCKET clientSocket) {
        clients.emplace(clientSocket, ClientData(clientSocket));
    }

    // Ŭ���̾�Ʈ ����
    void removeClient(SOCKET clientSocket) {
        clients.erase(clientSocket);
    }

    // ���� ���� ó��
    void incrementScore(SOCKET clientSocket) {
        if (clients.find(clientSocket) != clients.end()) {
            clients[clientSocket].incrementCorrectAnswers();
        }
    }

    // ���� ���� ����
    void setCurrentQuestion(SOCKET clientSocket, const std::string& question) {
        if (clients.find(clientSocket) != clients.end()) {
            clients[clientSocket].setCurrentQuestion(question);
        }
    }

    // ���� ���� ��������
    std::string getCurrentQuestion(SOCKET clientSocket) {
        if (clients.find(clientSocket) != clients.end()) {
            return clients[clientSocket].getCurrentQuestion();
        }
        return "";
    }

    // ���� ��������
    int getScore(SOCKET clientSocket) {
        if (clients.find(clientSocket) != clients.end()) {
            return clients[clientSocket].getCorrectAnswers();
        }
        return 0;
    }
};
*/