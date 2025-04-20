#pragma once

#include "Base/DDServerBaseObject.h"

#include <winsock2.h>

#include "Header/DDServerBaseMacro.h"
#include "Header/DDServerBaseStruct.h"


class API_DDSERVERBASE_CLASS CDDIOCPObject : public CDDServerBaseObject
{
	friend class CDDIOCPListener;

public:
	CDDIOCPObject();
	virtual ~CDDIOCPObject();

public:
	virtual void            Initialize() override;
	virtual bool            InitializeSocket();
	virtual void            InitializeOverlapped();
	virtual void            PostInitializeOverlapped();
	virtual void            PreConnect();
	virtual void            OnConnect();
	virtual void            PostConnect();
	virtual void            OnDisconnect();
	virtual void            PostDisconnect();
	virtual void            Release() override;
	virtual void            Dispatch(struct FDDOverlapped* Overlapped, const DWORD& BytesTransferred);

public:
	bool                    IsDisconnect();
	bool                    InvalidSocket();
	SOCKET                  GetSocket();

protected:
	void                    Private_ReleaseSocket();
	bool                    Private_InitializeIOCPSocket(HANDLE IOCPHandle);
	void                    Private_ReleaseIOCPSocket();

protected:
	SOCKET                 Socket        = INVALID_SOCKET;
	HANDLE                 IOCPHandleSet = INVALID_HANDLE_VALUE;
	sockaddr_in            SocketAddress;

	FIOCPNetInfo           IOCPNetInfo;
	DWORD                  OperationType;

};
