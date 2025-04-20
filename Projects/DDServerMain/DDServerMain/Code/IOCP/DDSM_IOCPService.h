#pragma once

#include "IOCP/Server/DDIOCPServiceServer.h"
#include "Header/DDServerMainMacro.h"


class API_DDSERVERMAIN_CLASS CDDSM_IOCPService : public CDDIOCPServiceServer
{
public:
	CDDSM_IOCPService();
	virtual ~CDDSM_IOCPService();

public:
	virtual void Initialize() override;
	virtual void Release() override;

protected:
	virtual void InitializeRegisterPacketMsgMethod() override;
	virtual class CDDIOCPSession* CreateSession() override;
	virtual class CDDIOCPThreadWorker* CreateThreadWork() override;
	virtual class CDDIOCPListener* CreateListener() override;

private:
	void RecievePacket_Request_Login_Google(const struct FDDReceivedMsgData* ReceivedMsgData);

};

