#pragma once

#include <winsock.h>


extern int ResultWSAStartup;
extern WSADATA WSAData;

void DDServerBaseInitialize();
void DDServerBaseRelease();