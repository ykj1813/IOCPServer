#pragma once

#include "IOCP/DDIOCPObject.h"
#include <list>
#include <vector>
#include <map>

#include "Header/DDServerBaseType.h"


class API_DDSERVERBASE_CLASS CDDIOCPListener : public CDDIOCPObject
{
public:
	CDDIOCPListener();
	virtual ~CDDIOCPListener();

public:
	virtual void                  Initialize() override;
	virtual bool                  InitializeSocket() override;
	virtual void                  InitializeOverlapped() override;
	virtual void                  PostInitializeOverlapped() override;
	virtual void                  PreConnect() override;
	virtual void                  OnConnect() override;
	virtual void                  PostConnect() override;
	virtual void                  OnDisconnect() override;
	virtual void                  PostDisconnect() override;
	virtual void                  Release() override;
	
	void                          SetupAcceptEx(SessionServerPtr Session);
	bool		                  OpenSocket(HANDLE IOCPHandle, FIOCPNetInfo IOCPNetInfo);

protected:
	virtual FDDOverlappedAccept*  CreateOverlappedAccept();
	virtual size_t                GetOverlappedAcceptSize() const;
	virtual void                  Dispatch(struct FDDOverlapped* Overlapped, const DWORD& BytesTransferred);

private:
	HANDLE                        IOCPHandle;
	FNetAddress                   NetAddress;
	std::vector<FIOCPWorkInfo>       m_Workers;
	// std::thread                      m_MainWorkThread;
	// std::list<ListenerWorkerPtr>     m_Workers;
	std::list<DDOverlappedAcceptPtr> m_OverlappedAccepts;

};
