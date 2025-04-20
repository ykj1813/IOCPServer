#include "pch.h"
#include "IOCP/Client/DDIOCPSessionClient.h"
#include <mswsock.h>


CDDIOCPSessionClient::CDDIOCPSessionClient()
{

}

CDDIOCPSessionClient::~CDDIOCPSessionClient()
{

}

void CDDIOCPSessionClient::Initialize()
{
	Super::Initialize();

	LOCK_GUARD(Mutex);

}

bool CDDIOCPSessionClient::InitializeSocket()
{
	bool ret = Super::InitializeSocket();

	LOCK_GUARD(Mutex);

	SOCKADDR_IN localAddr = { 0 };
	localAddr.sin_family = AF_INET;
	localAddr.sin_addr.s_addr = INADDR_ANY;
	localAddr.sin_port = 0;  // 시스템이 자동으로 포트를 할당하도록 설정

	if (SOCKET_ERROR == ::bind(Socket, (SOCKADDR*)&localAddr, sizeof(localAddr)))
	{
		ret = false;
	}

	return ret;
}

void CDDIOCPSessionClient::PostInitializeOverlapped()
{
	Super::PostInitializeOverlapped();

	LOCK_GUARD(Mutex);

}

void CDDIOCPSessionClient::PreConnect()
{
	Super::PreConnect();

	LOCK_GUARD(Mutex);

}

void CDDIOCPSessionClient::OnConnect()
{
	Super::OnConnect();

	LOCK_GUARD(Mutex);

}

void CDDIOCPSessionClient::PostConnect()
{
	Super::PostConnect();

	LOCK_GUARD(Mutex);

}

void CDDIOCPSessionClient::OnDisconnect()
{
	Super::OnDisconnect();

	LOCK_GUARD(Mutex);

}

void CDDIOCPSessionClient::PostDisconnect()
{
	Super::PostDisconnect();

	LOCK_GUARD(Mutex);

}

void CDDIOCPSessionClient::Release()
{
	Super::Release();

}
