#pragma once
#include <WinSock2.h>
#include <string>

#define MAX_BUF_SIZE 256

void SendMessageToClient(const SOCKET& clientSocket, int message[], int size);
//void HandleClientCommand(const SOCKET& clientSocket, const std::string command);
void HandleClientCommand(const SOCKET& clientSocket, int command[], int size);

void SendMessageToClient_ex7(const SOCKET& clientSocket, char message[][MAX_BUF_SIZE], int size);
void HandleClientCommand_ex7(const SOCKET& clientSocket, char command[][MAX_BUF_SIZE], int size);