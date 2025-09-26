#pragma once
#include <WinSock2.h>

#define MAX_BUF_SIZE 256
 
void SendMessageToClient(const SOCKET& clientSocket, const char* message);

void HandleClientCommand(const SOCKET& clientSocket, const char* command);