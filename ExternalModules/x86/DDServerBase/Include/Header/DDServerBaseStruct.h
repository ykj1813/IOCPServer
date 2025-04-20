#pragma once

#include <ws2tcpip.h>

#include "Header/DDServerBaseMacro.h"
#include "Header/DDServerBaseEnum.h"
#include "Header/DDServerBaseType.h"


struct API_DDSERVERBASE_STRUCT FIOCPInfo
{
	char IPv4[INET_ADDRSTRLEN] = "";
	unsigned short Port = 0;
};

struct API_DDSERVERBASE_STRUCT FIOCPThreadInfo
{
	unsigned short WorkerThreadNum;

};

struct API_DDSERVERBASE_STRUCT FIOCPThreadStatus
{
	bool isRunThread;
};

struct API_DDSERVERBASE_STRUCT FThreadEvent
{
	EThreadEvent Event = EThreadEvent::Unknown;
};

struct API_DDSERVERBASE_STRUCT FDDOverlapped
{
	OVERLAPPED Overlapped = { 0, };
};

struct API_DDSERVERBASE_STRUCT FDDOverlappedSession : public FDDOverlapped
{
	TSessionId SessionId = -1;
};

struct API_DDSERVERBASE_STRUCT FDDReceivedMsgData
{
	class CDDIOCPSession* Session;
	struct FDDBasePacket* Packet;
};
