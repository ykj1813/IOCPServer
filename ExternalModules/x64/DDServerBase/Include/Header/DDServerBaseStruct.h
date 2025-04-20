#pragma once

#include <ws2tcpip.h>

#include "Header/DDServerBaseMacro.h"
#include "Header/DDServerBaseEnum.h"
#include "Header/DDServerBaseType.h"
#include "Network/NetAddress.h"
#include "Network/NetBuffer.h"


struct API_DDSERVERBASE_STRUCT FIOCPNetInfo
{
	FNetAddress NetAddress;

};

struct API_DDSERVERBASE_STRUCT FIOCPInfo
{
	FIOCPNetInfo NetInfo;

	uint16 SessionNum = 1;
	uint8  WorkerThreadNum = 1;

	void SetNetInfo(const WCHAR* IP, uint16 Port)
	{
		NetInfo.NetAddress = FNetAddress(IP, Port);
	}
};

struct API_DDSERVERBASE_STRUCT FIOCPWorkInfo
{
	HANDLE      IOCPHandle = INVALID_HANDLE_VALUE;
};

struct API_DDSERVERBASE_STRUCT FThreadEvent
{
	EThreadEvent Event = EThreadEvent::Unknown;
};

struct API_DDSERVERBASE_STRUCT FDDOverlapped
{
	OVERLAPPED Overlapped = { 0, };
	EOverlappedType Type = EOverlappedType::Unknown;
	class CDDIOCPObject* Owner = nullptr;
	TSessionId SessionId = -1;
	struct FIOCPWorkInfo* WorkInfo;

	OVERLAPPED* GetOverlappedRawPtr() { return &Overlapped; }
};

struct API_DDSERVERBASE_STRUCT FDDOverlappedAccept : public FDDOverlapped
{
	FDDOverlappedAccept() { Type = EOverlappedType::Accept; }

	SessionServerPtr Session;
};

struct API_DDSERVERBASE_STRUCT FDDOverlappedConnect : public FDDOverlapped
{
	FDDOverlappedConnect() { Type = EOverlappedType::Connect; }

};

struct API_DDSERVERBASE_STRUCT FDDOverlappedDisconnect : public FDDOverlapped
{
	FDDOverlappedDisconnect() { Type = EOverlappedType::Disconnect; }

};

struct API_DDSERVERBASE_STRUCT FDDOverlappedRecv : public FDDOverlapped
{
	FDDOverlappedRecv() { Type = EOverlappedType::Receive; }

	class FNetBuffer* RecvBuffer = nullptr;
	WSABUF WSABuffer;
};

struct API_DDSERVERBASE_STRUCT FDDOverlappedSend : public FDDOverlapped
{
	FDDOverlappedSend() { Type = EOverlappedType::Send; }

	class FNetBuffer* SendBuffer = nullptr;
};

struct API_DDSERVERBASE_STRUCT FDDReceivedMsgData
{
	class CDDIOCPSession* Session;
	const struct FDDBasePacket* Packet;
};

struct API_DDSERVERBASE_STRUCT FDDSessionOverlapped
{
	DDOverlappedConnectPtr    ConnectPtr;
	DDOverlappedDisconnectPtr DisconnectPtr;
	DDOverlappedSendPtr       SendPtr;
	DDOverlappedRecvPtr       RecvPtr;

	void Initialize(TSessionId SessionId, class CDDIOCPObject* Owner)
	{
		ConnectPtr->SessionId    = SessionId;
		DisconnectPtr->SessionId = SessionId;
		SendPtr->SessionId       = SessionId;
		RecvPtr->SessionId       = SessionId;

		ConnectPtr->Owner        = Owner;
		DisconnectPtr->Owner     = Owner;
		SendPtr->Owner           = Owner;
		RecvPtr->Owner           = Owner;
	}
};