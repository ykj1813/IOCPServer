#pragma once

#include "IOCP/DDIOCPSession.h"
#include <map>
#include <functional>

#include "Header/DDServerBaseType.h"
#include "Network/NetAddress.h"


class API_DDSERVERBASE_CLASS CDDIOCPSessionServer : public CDDIOCPSession
{
public:
	CDDIOCPSessionServer();
	virtual ~CDDIOCPSessionServer();

public:
	virtual void Initialize() override;
	virtual bool InitializeSocket() override;
	virtual void PostInitializeOverlapped() override;
	virtual void PreConnect() override;
	virtual void OnConnect() override;
	virtual void PostConnect() override;
	virtual void OnDisconnect() override;
	virtual void PostDisconnect() override;
	virtual void Release() override;

};
