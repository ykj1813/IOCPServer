#pragma once

#include "IOCP/DDIOCPService.h"
#include "Interface/IDDThreadEvent.h"
#include <list>
#include <vector>
#include <map>

#include "Header/DDServerBaseType.h"


class API_DDSERVERBASE_CLASS CDDIOCPServiceClient : public CDDIOCPService
{
public:
	CDDIOCPServiceClient();
	virtual ~CDDIOCPServiceClient();

public:
	virtual void          Initialize() override;
	// virtual void                  InitializeRegisterPacketMsgMethod();
	// virtual bool                  InitializeSocket() override;
	// virtual void                  InitializeOverlapped() override;
	// virtual void                  PostInitializeOverlapped() override;
	// virtual void                  PreConnect() override;
	// virtual void                  OnConnect() override;
	// virtual void                  PostConnect() override;
	// virtual void                  OnDisconnect() override;
	// virtual void                  PostDisconnect() override;
	virtual void          Release() override;

	bool                  SendPacket(const struct FDDBasePacket* Packet);
	

protected:
	class CDDIOCPSession* CreateSession() override;
	virtual void          PreStartService() override;
	virtual void          OnStartService() override;
	virtual void          PostStartService() override;

};

