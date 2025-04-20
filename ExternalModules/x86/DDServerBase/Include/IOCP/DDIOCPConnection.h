#pragma once

#include "IOCP/DDIOCPObject.h"


class API_DDSERVERBASE_CLASS CDDIOCPConnection : public CDDIOCPObject
{
public:
	CDDIOCPConnection();
	virtual ~CDDIOCPConnection();

public:
	virtual void Initialize();
	virtual void Release();

public:
	virtual void BeginConnect();
	virtual void EndConnect();
	virtual void Disconnect();
	virtual void PostDisconnect();

public:


};
