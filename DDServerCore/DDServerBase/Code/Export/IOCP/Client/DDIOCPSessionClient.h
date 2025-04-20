#pragma once

#include "IOCP/DDIOCPSession.h"


class API_DDSERVERBASE_CLASS CDDIOCPSessionClient : public CDDIOCPSession
{
public:
	CDDIOCPSessionClient();
	virtual ~CDDIOCPSessionClient();

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
