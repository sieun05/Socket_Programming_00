#pragma once
//#define _CRT_SECURE_NO_WARNINGS
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#include <Windows.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

#define PORT 3500
#define MAX_BUF_SIZE 256
#define FD_SETSIZE 100
#define MAX_CLIENT 100

using namespace std;