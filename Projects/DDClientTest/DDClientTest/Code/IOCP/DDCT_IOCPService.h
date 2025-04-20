#pragma once

#include "IOCP/Client/DDIOCPServiceClient.h"
#include "Header/DDClientTestMacro.h"


class API_DDCLIENTTEST_CLASS CDDCT_IOCPService : public CDDIOCPServiceClient
{
public:
	CDDCT_IOCPService();
	virtual ~CDDCT_IOCPService();

public:
	virtual void Initialize() override;
	virtual void Release() override;

protected:
	virtual void InitializeRegisterPacketMsgMethod() override;
	virtual class CDDIOCPSession* CreateSession() override;

private:
	void TestMsg(const struct FDDReceivedMsgData* MsgData);

};

