#include "pch.h"
#include "DDIOCPSession.h"
#include <mswsock.h>

#include "Base/DDBasePacket.h"

#include "Utility/DDServerBaseSocketUtils.h"


CDDIOCPSession::CDDIOCPSession()
{
	m_ConnectionId = -1;

	// RecvBuffer = FNetBuffer(1024);
	// SendBuffer = FNetBuffer(1024);
}

CDDIOCPSession::~CDDIOCPSession()
{

}

void CDDIOCPSession::Initialize()
{
	Super::Initialize();

 	InitializeSocket();

	ULONG_PTR CompletionKey = 0;
	HANDLE result = ::CreateIoCompletionPort((HANDLE)Socket, IOCPHandleSet, CompletionKey, 0);
}

bool CDDIOCPSession::InitializeSocket()
{
	bool ret = Super::InitializeSocket();

	LOCK_GUARD(Mutex);

	return ret;
}

void CDDIOCPSession::InitializeOverlapped()
{
	Super::InitializeOverlapped();

	LOCK_GUARD(Mutex);

	DDOverlappedConnectPtr OverlappedConnectPtr = CreateOverlappedConnect();
	// ZeroMemory(OverlappedConnectPtr.get(), GetOverlappedConnectSize());
	Overlappeds.ConnectPtr = OverlappedConnectPtr;

	DDOverlappedDisconnectPtr OverlappedDisconnectPtr = CreateOverlappedDisconnect();
	// ZeroMemory(OverlappedDisconnectPtr.get(), GetOverlappedDisconnectSize());
	Overlappeds.DisconnectPtr = OverlappedDisconnectPtr;

	DDOverlappedSendPtr OverlappedSendPtr = CreateOverlappedSend();
	// ZeroMemory(OverlappedSendPtr.get(), GetOverlappedSendSize());
	Overlappeds.SendPtr = OverlappedSendPtr;
	Overlappeds.SendPtr->SendBuffer = &this->SendBuffer;

	DDOverlappedRecvPtr OverlappedRecvPtr = CreateOverlappedRecv();
	// ZeroMemory(OverlappedRecvPtr.get(), GetOverlappedRecvSize());
	Overlappeds.RecvPtr = OverlappedRecvPtr;
	Overlappeds.RecvPtr->RecvBuffer = &this->RecvBuffer;

	Overlappeds.Initialize(m_ConnectionId, this);
}

void CDDIOCPSession::PostInitializeOverlapped()
{
	Super::PostInitializeOverlapped();

	LOCK_GUARD(Mutex);

}

void CDDIOCPSession::PreConnect()
{
	Super::PreConnect();

	LOCK_GUARD(Mutex);

}

void CDDIOCPSession::OnConnect()
{
	Super::OnConnect();

	LOCK_GUARD(Mutex);

}

void CDDIOCPSession::PostConnect()
{
	Super::PostConnect();

	LOCK_GUARD(Mutex);

}

void CDDIOCPSession::OnDisconnect()
{
	Super::OnDisconnect();

	SetupAcceptEx(ListenSocket, OverlappedAcceptPtr);
}

void CDDIOCPSession::PostDisconnect()
{
	Super::PostDisconnect();

	LOCK_GUARD(Mutex);

}

void CDDIOCPSession::SetupRecvPacketMethod(std::function<void(class CDDIOCPSession*, const struct FDDBasePacket*)> RecvFunction)
{
	LOCK_GUARD(Mutex);

	m_RecvPacketFunction = RecvFunction;
}

void CDDIOCPSession::Release()
{
	Super::Release();

}

bool CDDIOCPSession::SetupAcceptEx(SOCKET ListenSocket, DDOverlappedAcceptPtr OverlappedAccept)
{
	if (true == InvalidSocket())
	{
		return false;
	}

	LOCK_GUARD(Mutex);

	sockaddr_in ClientAddress;
	int32 addrLen = sizeof(ClientAddress);
	DWORD ReceiveByte = 0;

	this->ListenSocket = ListenSocket;
	this->OverlappedAcceptPtr = OverlappedAccept;

	BOOL Result = dds::AcceptEx(ListenSocket, Socket, RecvBuffer.GetBuffer(), 0, sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16, &ReceiveByte, reinterpret_cast<LPOVERLAPPED>(OverlappedAccept.get()));
	if (TRUE != Result)
	{
		const int32 ErrorCode = ::WSAGetLastError();
		if (WSA_IO_PENDING == ErrorCode)
		{
			Result = TRUE;
		}

	}

	return TRUE == Result;
}

bool CDDIOCPSession::SetupConnectEx(const FNetAddress* NetAddresss)
{
	DWORD numOfBytes = 0;
	SOCKADDR_IN sockAddr = NetAddresss->GetSockAddrRaw();
	BOOL Result = dds::ConnectEx(Socket, reinterpret_cast<SOCKADDR*>(&sockAddr), sizeof(sockAddr), nullptr, 0, &numOfBytes, Overlappeds.ConnectPtr->GetOverlappedRawPtr());
	if (TRUE != Result)
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode == WSA_IO_PENDING)
		{
			// _connectEvent.owner = nullptr; // RELEASE_REF
			Result = TRUE;
		}
	}

	return TRUE == Result;
}

bool CDDIOCPSession::SetupDisconnectEx()
{
	BOOL Result = dds::DisconnectEx(Socket, Overlappeds.DisconnectPtr->GetOverlappedRawPtr(), TF_REUSE_SOCKET, 0);
	if (TRUE != Result)
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode == WSA_IO_PENDING)
		{
			// _disconnectEvent.owner = nullptr; // RELEASE_REF
			Result = TRUE;
		}
	}

	return TRUE == Result;
}

bool CDDIOCPSession::SetupWSASend()
{
	// if (IsConnected() == false)
	// 	return;
	// 
	// _sendEvent.Init();
	// _sendEvent.owner = shared_from_this(); // ADD_REF

	// 보낼 데이터를 sendEvent에 등록
	// {
	// 	WRITE_LOCK;
	// 
	// 	int32 writeSize = 0;
	// 	while (_sendQueue.empty() == false)
	// 	{
	// 		SendBufferRef sendBuffer = _sendQueue.front();
	// 
	// 		writeSize += sendBuffer->WriteSize();
	// 		// TODO : 예외 체크
	// 
	// 		_sendQueue.pop();
	// 		_sendEvent.sendBuffers.push_back(sendBuffer);
	// 	}
	// }

	// Scatter-Gather (흩어져 있는 데이터들을 모아서 한 방에 보낸다)
	// Vector<WSABUF> wsaBufs;
	// wsaBufs.reserve(_sendEvent.sendBuffers.size());
	// for (SendBufferRef sendBuffer : _sendEvent.sendBuffers)
	// {
		WSABUF wsaBuf;
		wsaBuf.buf = reinterpret_cast<char*>(SendBuffer.GetBuffer());
		wsaBuf.len = static_cast<LONG>(SendBuffer.GetWritePos());
		// wsaBufs.push_back(wsaBuf);
	// }

	DWORD numOfBytes = 0;
	bool rt = true;
	if (SOCKET_ERROR == ::WSASend(Socket, &wsaBuf, 1, OUT & numOfBytes, 0, Overlappeds.SendPtr->GetOverlappedRawPtr(), nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			// HandleError(errorCode);
			// _sendEvent.owner = nullptr; // RELEASE_REF
			// _sendEvent.sendBuffers.clear(); // RELEASE_REF
			// _sendRegistered.store(false);

			rt = false;
		}
	}

	return rt;
}

bool CDDIOCPSession::SetupWSARecv(TSocketError* OUT ErrorCode)
{
	bool rt = true;

	WSABUF wsaBuf;
	wsaBuf.buf = reinterpret_cast<char*>(RecvBuffer.GetBuffer());
	wsaBuf.len = sizeof(RecvBuffer.GetSize());

	DWORD numOfBytes = 0;
	DWORD flags = 0;
	if (nullptr != ErrorCode)
	{
		*ErrorCode = SOCKET_ERROR;
	}

	Overlappeds.RecvPtr->RecvBuffer->Clear();
	if (SOCKET_ERROR == ::WSARecv(Socket, &wsaBuf, 1, OUT & numOfBytes, OUT & flags, Overlappeds.RecvPtr->GetOverlappedRawPtr(), nullptr))
	{
		TSocketError LastErrorCode = ::WSAGetLastError();
		if (nullptr != ErrorCode)
		{
			*ErrorCode = LastErrorCode;
		}

		if (LastErrorCode != WSA_IO_PENDING)
		{
			// HandleError(errorCode);
			// _recvEvent.owner = nullptr; // RELEASE_REF
			rt = false;
		}
	}
	else
	{
		if (nullptr != ErrorCode)
		{
			*ErrorCode = 0;
		}

		// OnProcessRecvPacket(static_cast<FDDOverlappedRecv*>(Overlappeds.RecvPtr.get()));
	}

	return rt;
}

bool CDDIOCPSession::SendPacket(const FDDBasePacket* Packet)
{
	bool rt = false;

	SendBuffer.WriteBuffer(reinterpret_cast<const char*>(Packet), Packet->Header.Size);

	rt = SetupWSASend();

	return rt;
}

void CDDIOCPSession::Dispatch(FDDOverlapped* Overlapped, const DWORD& BytesTransferred)
{
	Super::Dispatch(Overlapped, BytesTransferred);

	TSocketError ErrorCode = 0;

	switch (Overlapped->Type)
	{
	case EOverlappedType::Connect:
		OnProcessConnect();
		break;

	case EOverlappedType::Disconnect:
		OnProcessDisconnect();
		break;

	case EOverlappedType::Receive:		
		if (true == OnProcessRecvPacket(reinterpret_cast<FDDOverlappedRecv*>(Overlapped), BytesTransferred))
		{
			SetupWSARecv(&ErrorCode);
		}
		else
		{
			SetupDisconnectEx();
		}
		break;

	case EOverlappedType::Send:
		OnProcessSendPacket(reinterpret_cast<FDDOverlappedSend*>(Overlapped), BytesTransferred);
		break;

	default:
		break;
	}

}

DDOverlappedConnectPtr CDDIOCPSession::CreateOverlappedConnect() const
{
	return DDOverlappedConnectPtr(new FDDOverlappedConnect);
}

size_t CDDIOCPSession::GetOverlappedConnectSize() const
{
	return sizeof(FDDOverlappedConnect);
}

DDOverlappedDisconnectPtr CDDIOCPSession::CreateOverlappedDisconnect() const
{
	return DDOverlappedDisconnectPtr(new FDDOverlappedDisconnect);
}

size_t CDDIOCPSession::GetOverlappedDisconnectSize() const
{
	return sizeof(FDDOverlappedDisconnect);
}

DDOverlappedSendPtr CDDIOCPSession::CreateOverlappedSend() const
{
	return DDOverlappedSendPtr(new FDDOverlappedSend);
}

size_t CDDIOCPSession::GetOverlappedSendSize() const
{
	return sizeof(FDDOverlappedSend);
}

DDOverlappedRecvPtr CDDIOCPSession::CreateOverlappedRecv() const
{
	return DDOverlappedRecvPtr(new FDDOverlappedRecv);
}

size_t CDDIOCPSession::GetOverlappedRecvSize() const
{
	return sizeof(FDDOverlappedRecv);
}

void CDDIOCPSession::SetIOCP(HANDLE _IOCPHandle)
{
	LOCK_GUARD(Mutex);

	Private_ReleaseIOCPSocket();

	Private_InitializeIOCPSocket(_IOCPHandle);
}

void CDDIOCPSession::SetNetAddress(FNetAddress NetAddress)
{
	m_NetAddress = NetAddress;
}

void CDDIOCPSession::Stop()
{

}

void CDDIOCPSession::SetSessionId(TSessionId SessionId)
{
	m_ConnectionId = SessionId;
}

TSessionId CDDIOCPSession::GetSessionId() const
{
	return m_ConnectionId;
}

void CDDIOCPSession::OnProcessConnect()
{
	PreConnect();

	OnConnect();

	PostConnect();
}

void CDDIOCPSession::OnProcessDisconnect()
{
	OnDisconnect();

	PostDisconnect();
}

bool CDDIOCPSession::OnProcessRecvPacket(FDDOverlappedRecv* OverlappedRecv, const DWORD& BytesTransferred)
{
	if (!m_RecvPacketFunction)
	{
		return true;
	}
	if (0 == BytesTransferred)
	{
		return false;
	}

	PendingRecvBuffer.WriteBuffer(OverlappedRecv->RecvBuffer->GetBuffer(), BytesTransferred);
	FDDBasePacket* Packet = reinterpret_cast<FDDBasePacket*>(PendingRecvBuffer.GetBuffer());
	if (Packet->Header.Size == PendingRecvBuffer.GetWritePos() && 0 < PendingRecvBuffer.GetWritePos())
	{
		m_RecvPacketFunction(this, reinterpret_cast<FDDBasePacket*>(PendingRecvBuffer.GetBuffer()));
		PendingRecvBuffer.Clear();
	}

	return true;
}

void CDDIOCPSession::OnProcessSendPacket(FDDOverlappedSend* OverlappedSend, const DWORD& BytesTransferred)
{

}
