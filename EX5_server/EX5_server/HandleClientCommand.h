#pragma once
#include <WinSock2.h>
#include <string>

#define MAX_BUF_SIZE 256

void SendMessageToClient(const SOCKET& clientSocket, const char* message);
//void HandleClientCommand(const SOCKET& clientSocket, const std::string command);
void HandleClientCommand(const SOCKET& clientSocket, const int command);