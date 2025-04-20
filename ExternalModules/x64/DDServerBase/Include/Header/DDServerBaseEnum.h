#pragma once


enum class EOverlappedType
{
	  Unknown
	, Accept
	, Connect
	, Disconnect
	, Send
	, Receive
	, SessionServer
	, SessionClient
};

enum class EThreadEvent
{
	  Unknown
	, Stop
	, Max
};

enum class ENetworkFlag
{
	  None = 0x0000'0000
	, Disconnect = 0x0000'0001
};