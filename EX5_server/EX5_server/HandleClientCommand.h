#pragma once
#include "Çì´õ.h"
#include "Data.h"
#include "test_Data.h"
#include "ClientManager.h"
#include "Questions.h"

#define MAX_BUF_SIZE 256

void SendMessageToClient(const SOCKET& clientSocket, int message[], int size);
//void HandleClientCommand(const SOCKET& clientSocket, const std::string command);
void HandleClientCommand(const SOCKET& clientSocket, int command[], int size);

void SendMessageToClient_ex7(const SOCKET& clientSocket, char message[][MAX_BUF_SIZE], int size);
void HandleClientCommand_ex7(const SOCKET& clientSocket, char command[][MAX_BUF_SIZE], int size);

void SendMessageToClient_ex8(const SOCKET& clientSocket, Data data, int size);
void HandleClientCommand_ex8(const SOCKET& clientSocket, Data data, int size);

void SendMessageToClient_ex9(const SOCKET& clientSocket, Data data[], int size);
void HandleClientCommand_ex9(const SOCKET& clientSocket, Data data[], int size);

void SendMessageToClient_test(const SOCKET& clientSocket, test_Data data, int size);
void HandleClientCommand_test(const SOCKET& clientSocket, test_Data data, int size);