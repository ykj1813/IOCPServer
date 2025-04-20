#include "pch.h"
#include "DDIOCPObject.h"
#include <mswsock.h>

#include "Header/DDCommonStruct.h"
#include "Header/DDCommonMacro.h"

#include "Header/DDServerBaseFunction.h"
#include "Network/NetAddress.h"
#include "Utility/DDServerBaseSocketUtils.h"


CDDIOCPObject::CDDIOCPObject()
{

}

CDDIOCPObject::~CDDIOCPObject()
{

}

void CDDIOCPObject::Initialize()
{
	//	LOCK_GUARD(Mutex);

}

void CDDIOCPObject::Release()
{
	LOCK_GUARD(Mutex);

	Private_ReleaseIOCPSocket();

	Private_ReleaseSocket();
}

void CDDIOCPObject::PostDisconnect()
{
	LOCK_GUARD(Mutex);

}

bool CDDIOCPObject::InitializeSocket()
{
	LOCK_GUARD(Mutex);

	Socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO::IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == Socket)
	{
		throw std::runtime_error("Socket creation failed.");
		return false;
	}

	SetSockOpt(Socket, SOL_SOCKET, SO_REUSEADDR, true);

	LINGER lin;
	lin.l_onoff  = 0;
	lin.l_linger = 0;
	if (SOCKET_ERROR == setsockopt(Socket, SOL_SOCKET, SO_LINGER, reinterpret_cast<const char*>(&lin), sizeof(lin)))
	{
		throw std::runtime_error("Failed to set SO_LINGER.");
		return false;
	}
	 
	// Nagle 알고리즘 비활성화
	// BOOL bNodelayOption = TRUE;
	// if (SOCKET_ERROR == setsockopt(Socket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char*>(&bNodelayOption), sizeof(bNodelayOption)))
	// {
	// 	throw std::runtime_error("Failed to set TCP_NODELAY.");
	// 	return false;
	// }

	// 주소 재사용 허용
	// BOOL bReuseOption = TRUE;
	// if (SOCKET_ERROR == setsockopt(Socket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&bReuseOption), sizeof(bReuseOption)))
	// {
	// 	throw std::runtime_error("Failed to set SO_REUSEADDR.");
	// 	return false;
	// }

	// Linger 옵션 설정
	// LINGER lin;
	// lin.l_onoff = 1;
	// lin.l_linger = 0;
	// if (SOCKET_ERROR == setsockopt(Socket, SOL_SOCKET, SO_LINGER, reinterpret_cast<const char*>(&lin), sizeof(lin)))
	// {
	// 	throw std::runtime_error("Failed to set SO_LINGER.");
	// 	return false;
	// }

	return true;
}

void CDDIOCPObject::InitializeOverlapped()
{
	LOCK_SHARED(Mutex);

}

void CDDIOCPObject::PreConnect()
{
	LOCK_SHARED(Mutex);

}

void CDDIOCPObject::OnConnect()
{
	LOCK_SHARED(Mutex);

}

void CDDIOCPObject::PostConnect()
{
	LOCK_SHARED(Mutex);

}

void CDDIOCPObject::OnDisconnect()
{
	LOCK_GUARD(Mutex);

}

void CDDIOCPObject::PostInitializeOverlapped()
{

}

void CDDIOCPObject::Dispatch(FDDOverlapped* Overlapped, const DWORD& BytesTransferred)
{

}

void CDDIOCPObject::Private_ReleaseSocket()
{
	if (INVALID_SOCKET == Socket)
	{
		return;
	}

	closesocket(Socket);
	Socket = INVALID_SOCKET;
}

bool CDDIOCPObject::Private_InitializeIOCPSocket(HANDLE IOCPHandle)
{
	if (NULL == IOCPHandle || INVALID_HANDLE_VALUE == IOCPHandle)
	{
		IOCPHandleSet = INVALID_HANDLE_VALUE;
		return false;
	}

	IOCPHandleSet = IOCPHandle;

	return true;
}

void CDDIOCPObject::Private_ReleaseIOCPSocket()
{
	IOCPHandleSet = INVALID_HANDLE_VALUE;
}

bool CDDIOCPObject::IsDisconnect()
{
	LOCK_SHARED(Mutex);

	// return Socket == INVALID_SOCKET;
	return false;
}

bool CDDIOCPObject::InvalidSocket()
{
	LOCK_SHARED(Mutex);

	return Socket == INVALID_SOCKET;
}

SOCKET CDDIOCPObject::GetSocket()
{
	LOCK_SHARED(Mutex);

	return Socket;
}
