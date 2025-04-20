#include "pch.h"
#include "DDServerBase.h"
#include <stdexcept>
#include <WinSock2.h>

#include "Utility/DDServerBaseSocketUtils.h"

int ResultWSAStartup = -1;
WSADATA WSAData;

bool BindWSAFunction(SOCKET socket, GUID guid, LPVOID* fn)
{
	DWORD bytes = 0;
	return SOCKET_ERROR != ::WSAIoctl(socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guid, sizeof(guid), fn, sizeof(*fn), OUT & bytes, NULL, NULL);
}

void DDServerBaseInitialize()
{
	if (ResultWSAStartup = WSAStartup(MAKEWORD(2, 2), &WSAData))
	{
		throw std::runtime_error("WSAStartup failed");
	}

	SOCKET TempSocket = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	
	ASSERT_CRASH(BindWSAFunction(TempSocket, WSAID_ACCEPTEX    , reinterpret_cast<LPVOID*>(&dds::AcceptEx    )));
	ASSERT_CRASH(BindWSAFunction(TempSocket, WSAID_CONNECTEX   , reinterpret_cast<LPVOID*>(&dds::ConnectEx   )));
	ASSERT_CRASH(BindWSAFunction(TempSocket, WSAID_DISCONNECTEX, reinterpret_cast<LPVOID*>(&dds::DisconnectEx)));

	::closesocket(TempSocket);
}

void DDServerBaseRelease()
{
	if (0 == ResultWSAStartup)
	{
		WSACleanup();
	}
}
