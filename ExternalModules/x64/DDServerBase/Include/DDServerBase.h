#pragma once

#include <WinSock2.h>


extern int ResultWSAStartup;
extern WSADATA WSAData;

void DDServerBaseInitialize();
void DDServerBaseRelease();