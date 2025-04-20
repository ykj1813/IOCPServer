#pragma once

#include "IOCP/Server/DDIOCPSessionServer.h"
#include "Header/DDServerMainMacro.h"

#include "base/DDBasePacket.h"

struct FDDPacketTest : public FDDBasePacket
{
	int Test = 0;
};

class API_DDSERVERMAIN_CLASS CDDSM_IOCPSession : public CDDIOCPSessionServer
{
public:
	CDDSM_IOCPSession();
	virtual ~CDDSM_IOCPSession();

public:
	virtual void Initialize() override;
	virtual void Release() override;

};

