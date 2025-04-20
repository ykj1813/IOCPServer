#include "pch.h"
#include "DDIOCPListener.h"

#include <limits>
#include <cstdint>
#include <winsock2.h>
#include <mswsock.h>

#include "Header/DDCommonStruct.h"
#include "Base/DDBasePacket.h"

#include "Header/DDServerBaseFunction.h"
#include "IOCP/Server/DDIOCPSessionServer.h"


CDDIOCPListener::CDDIOCPListener()
{

}

CDDIOCPListener::~CDDIOCPListener()
{

}

void CDDIOCPListener::Initialize()
{
	Super::Initialize();

	InitializeSocket();

}

bool CDDIOCPListener::InitializeSocket()
{
	bool ret = Super::InitializeSocket();


	return ret;
}

void CDDIOCPListener::InitializeOverlapped()
{
	Super::InitializeOverlapped();

	LOCK_GUARD(Mutex);

}

void CDDIOCPListener::PostInitializeOverlapped()
{
	Super::PostInitializeOverlapped();

	LOCK_GUARD(Mutex);
	// ASSERT_CRASH(EOverlappedType::Accept == Overlapped->Type);

}

void CDDIOCPListener::PreConnect()
{
	Super::PreConnect();

	LOCK_GUARD(Mutex);
}

void CDDIOCPListener::OnConnect()
{
	Super::OnConnect();

	LOCK_GUARD(Mutex);

}

void CDDIOCPListener::PostConnect()
{
	Super::PostConnect();

	LOCK_GUARD(Mutex);

}

void CDDIOCPListener::OnDisconnect()
{
	Super::OnDisconnect();

	LOCK_GUARD(Mutex);

}

void CDDIOCPListener::PostDisconnect()
{
	Super::PostDisconnect();

	LOCK_GUARD(Mutex);

}

void CDDIOCPListener::Release()
{
	Super::Release();

	LOCK_GUARD(Mutex);

	//:: 미리 할당된 객체들 전부 해제
	m_OverlappedAccepts.clear();
}

void CDDIOCPListener::SetupAcceptEx(SessionServerPtr Session)
{
	DDOverlappedAcceptPtr AcceptPtr = DDOverlappedAcceptPtr(CreateOverlappedAccept());
	AcceptPtr->Owner = this;

	AcceptPtr->SessionId = Session->GetSessionId();
	AcceptPtr->Session = Session;
	Session->SetupAcceptEx(Socket, AcceptPtr);

	m_OverlappedAccepts.push_back(AcceptPtr);
}

bool CDDIOCPListener::OpenSocket(HANDLE IOCPHandle, FIOCPNetInfo IOCPNetInfo)
{
	this->IOCPNetInfo = IOCPNetInfo;

	if (false == InitializeSocket())
	{
		throw std::runtime_error("Socket creation failed");
		return false;
	}

	LOCK_GUARD(Mutex);

	if (false == Private_InitializeIOCPSocket(IOCPHandle))
	{
		throw std::runtime_error("CreateIoCompletionPort failed");
		return false;
	}
	CreateIoCompletionPort((HANDLE)Socket, IOCPHandleSet, 0, 0);

	sockaddr_in serverAddr = {};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = IOCPNetInfo.NetAddress.GetSockAddrRaw().sin_port;

	if (SOCKET_ERROR == bind(Socket, (sockaddr*)&serverAddr, sizeof(serverAddr)))
	{
		throw std::runtime_error("Bind failed");
		return false;
	}

	if (SOCKET_ERROR == listen(Socket, 10))
	{
		throw std::runtime_error("Listen failed");
		return false;
	}

	return true;
}

FDDOverlappedAccept* CDDIOCPListener::CreateOverlappedAccept()
{
	return new FDDOverlappedAccept;
}

size_t CDDIOCPListener::GetOverlappedAcceptSize() const
{
	return sizeof(FDDOverlappedAccept);
}

void CDDIOCPListener::Dispatch(FDDOverlapped* Overlapped, const DWORD& BytesTransferred)
{
	Super::Dispatch(Overlapped, BytesTransferred);

	ASSERT_CRASH(EOverlappedType::Accept == Overlapped->Type);
	FDDOverlappedAccept* Accept = static_cast<FDDOverlappedAccept*>(Overlapped);

	//:: 
	LOCK_GUARD(Mutex);

	SessionServerPtr Session = Accept->Session;
	if (nullptr == Session)
	{
		return;
	}

	Session->PreConnect();

	SetSockOpt(Session->GetSocket(), SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, Socket);

	Session->OnConnect();

	Session->PostConnect();

	Session->SetupWSARecv();

	int iBreakingPoint = 0;

}
