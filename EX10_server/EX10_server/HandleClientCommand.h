#pragma once
#include "Çì´õ.h"

#define MAX_BUF_SIZE 256

void SendMessageToClient(const SOCKET& clientSocket, int message[], int size);
void HandleClientCommand(const SOCKET& clientSocket, int command[], int size);