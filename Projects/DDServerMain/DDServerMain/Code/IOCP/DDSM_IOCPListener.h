#pragma once

#include "IOCP/Server/DDIOCPListener.h"
#include "Header/DDServerMainMacro.h"


class API_DDSERVERMAIN_CLASS CDDSM_IOCPListener : public CDDIOCPListener
{
public:
	CDDSM_IOCPListener();
	virtual ~CDDSM_IOCPListener();


public:
	virtual void Initialize() override;
	virtual void Release() override;

private:

};

