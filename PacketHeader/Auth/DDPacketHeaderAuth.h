#pragma once


#include "Base/DDBasePacket.h"

enum class EDDPacketAuth : TPacketId
{
	Request_Login_Google = 1,
	Response_Login_Google = 1,
};


struct API_DDSERVERBASE_PACKET FDDPacketRequestLoginGoogle : public FDDBasePacket
{
	FDDPacketRequestLoginGoogle()
		: FDDBasePacket((TPacketId)EDDPacketAuth::Request_Login_Google, sizeof(FDDPacketRequestLoginGoogle))
	{

	}
};

struct API_DDSERVERBASE_PACKET FDDPacketResponseLoginGoogle : public FDDBasePacket
{
	FDDPacketResponseLoginGoogle()
		: FDDBasePacket((TPacketId)EDDPacketAuth::Response_Login_Google, sizeof(FDDPacketResponseLoginGoogle))
	{

	}
};

