#pragma once

#include "IOCP/Client/DDIOCPSessionClient.h"
#include "Header/DDClientTestMacro.h"

#include "base/DDBasePacket.h"


struct FDDPacketTest : public FDDBasePacket
{
	int Test = 0;
};

class API_DDCLIENTTEST_CLASS CDDCT_IOCPSession : public CDDIOCPSessionClient
{
public:
	CDDCT_IOCPSession();
	virtual ~CDDCT_IOCPSession();

public:
	virtual void Initialize() override;
	virtual void Release() override;

};

