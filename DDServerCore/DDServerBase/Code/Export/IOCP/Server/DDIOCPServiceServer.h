#pragma once

#include "IOCP/DDIOCPService.h"
#include "Interface/IDDThreadEvent.h"
#include <list>
#include <vector>
#include <map>

#include "Header/DDServerBaseType.h"


class API_DDSERVERBASE_CLASS CDDIOCPServiceServer : public CDDIOCPService
{
public:
	CDDIOCPServiceServer();
	CDDIOCPServiceServer(const WCHAR* IP, uint16 Port, uint16 SessionNum, uint8 WorkerThreadNum);
	virtual ~CDDIOCPServiceServer();

public:
	virtual void                  Initialize() override;
	// virtual bool                  InitializeSocket() override;
	// virtual void                  InitializeOverlapped() override;
	// virtual void                  PostInitializeOverlapped() override;
	// virtual void                  PreConnect() override;
	// virtual void                  OnConnect() override;
	// virtual void                  PostConnect() override;
	// virtual void                  OnDisconnect() override;
	// virtual void                  PostDisconnect() override;
	virtual void                  Release() override;

protected:
	virtual class CDDIOCPSession*       CreateSession() override;
	virtual class CDDIOCPListener*      CreateListener();
	virtual struct FDDOverlappedAccept* CreateOverlappedAccept();

	virtual void                        PreStartService() override;
	virtual void                        OnStartService() override;
	virtual void                        PostStartService() override;

public:
	size_t                        GetDefaultReserveSessionSize();
	size_t                        GetDefaultReserveWorkerSize();
	size_t                        GetConnectionNum();
	size_t                        GetReserveSessionNum();

private:
	ListenerPtr                   m_Listener;



};

