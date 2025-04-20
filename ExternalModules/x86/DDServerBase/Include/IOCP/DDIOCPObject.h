#pragma once

#include "Base/DDServerBaseObject.h"

#include <winsock2.h>

#include "Header/DDServerBaseMacro.h"
#include "Header/DDServerBaseStruct.h"


class API_DDSERVERBASE_CLASS CDDIOCPObject : public CDDServerBaseObject
{
public:
	CDDIOCPObject();
	virtual ~CDDIOCPObject();

public:
	virtual void     Initialize() override;
	virtual void     Release() override;

public:
	virtual bool     InitializeSocket();
	virtual void     BeginConnect();
	virtual void     EndConnect();
	virtual void     Disconnect();
	virtual void     PostDisconnect();

protected:
	virtual DDOverlappedPtr CreateOverlapped() const;
	virtual size_t          GetOverlappedSize() const;
	virtual void            PostInitializeOverlapped(DDOverlappedPtr Overlapped);

public:
	bool                    IsDisconnect();
	SOCKET                  GetSocket();
	FIOCPInfo               GetIOCPInfo();

protected:
	void                    Private_ReleaseSocket();
	bool                    Private_InitializeIOCPSocket(HANDLE _IOCPHandle);
	void                    Private_ReleaseIOCPSocket();

protected:
	SOCKET Socket = INVALID_SOCKET;
	HANDLE IOCPHandleSet = INVALID_HANDLE_VALUE;
	HANDLE IOCPHandle = INVALID_HANDLE_VALUE;
	sockaddr_in SocketAddress;
	DDOverlappedPtr OverlappedPtr = nullptr;
	char Buffer[1024] = "";

	FIOCPInfo IOCPInfo;
	WSABUF WSABufffer;
	DWORD BytesTransferred;
	DWORD OperationType;

};
