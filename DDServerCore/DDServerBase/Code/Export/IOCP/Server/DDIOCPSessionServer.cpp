#include "pch.h"
#include "DDIOCPSessionServer.h"
#include <mswsock.h>


CDDIOCPSessionServer::CDDIOCPSessionServer()
{

}

CDDIOCPSessionServer::~CDDIOCPSessionServer()
{

}

void CDDIOCPSessionServer::Initialize()
{
	Super::Initialize();

	LOCK_GUARD(Mutex);

}

bool CDDIOCPSessionServer::InitializeSocket()
{
	bool ret = Super::InitializeSocket();

	LOCK_GUARD(Mutex);

	return ret;
}

void CDDIOCPSessionServer::PostInitializeOverlapped()
{
	Super::PostInitializeOverlapped();

	LOCK_GUARD(Mutex);

}

void CDDIOCPSessionServer::PreConnect()
{
	Super::PreConnect();

	LOCK_GUARD(Mutex);

}

void CDDIOCPSessionServer::OnConnect()
{
	Super::OnConnect();

	LOCK_GUARD(Mutex);

	// SOCKADDR_IN SockAddress;
	// int32 sizeOfSockAddr = sizeof(SockAddress);
	// if (SOCKET_ERROR == ::getpeername(Socket, OUT reinterpret_cast<SOCKADDR*>(&SockAddress), &sizeOfSockAddr))
	// {
	// 	return;
	// }
	// 
	// SetNetAddress(SockAddress);
	// 
	// 
	// WSABUF wsaBuf;
	// wsaBuf.buf = reinterpret_cast<char*>(Buffer);
	// wsaBuf.len = sizeof(Buffer);
	// 
	// DWORD numOfBytes = 0;
	// DWORD flags = 0;
	// if (SOCKET_ERROR == ::WSARecv(Socket, &wsaBuf, 1, OUT & numOfBytes, OUT & flags, GetPtrOverlapped(), nullptr))
	// {
	// 	int32 errorCode = ::WSAGetLastError();
	// 	if (errorCode != WSA_IO_PENDING)
	// 	{
	// 		HandleError(errorCode);
	// 		_recvEvent.owner = nullptr; // RELEASE_REF
	// 	}
	// }

	// WSABUF wsaBuf;
	// wsaBuf.buf = reinterpret_cast<char*>(_recvBuffer.WritePos());
	// wsaBuf.len = _recvBuffer.FreeSize();
	// 
	// DWORD numOfBytes = 0;
	// DWORD flags = 0;
	// if (SOCKET_ERROR == ::WSARecv(_socket, &wsaBuf, 1, OUT & numOfBytes, OUT & flags, &_recvEvent, nullptr))
	// {
	// 	int32 errorCode = ::WSAGetLastError();
	// 	if (errorCode != WSA_IO_PENDING)
	// 	{
	// 		HandleError(errorCode);
	// 		_recvEvent.owner = nullptr; // RELEASE_REF
	// 	}
	// }
}

void CDDIOCPSessionServer::PostConnect()
{
	Super::PostConnect();

	LOCK_GUARD(Mutex);

}

void CDDIOCPSessionServer::OnDisconnect()
{
	Super::OnDisconnect();

	LOCK_GUARD(Mutex);

}

void CDDIOCPSessionServer::PostDisconnect()
{
	Super::PostDisconnect();

	LOCK_GUARD(Mutex);

}

void CDDIOCPSessionServer::Release()
{
	Super::Release();

}
