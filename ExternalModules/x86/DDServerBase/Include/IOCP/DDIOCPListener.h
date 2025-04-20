#pragma once

#include "IOCP/DDIOCPObject.h"
#include "Interface/IDDThreadEvent.h"
#include <list>
#include <vector>
#include <map>

#include "Header/DDServerBaseType.h"


class API_DDSERVERBASE_CLASS CDDIOCPListener : public CDDIOCPObject, public IDDThreadEvent
{
public:
	CDDIOCPListener();
	virtual ~CDDIOCPListener();

public:
	virtual void                  Initialize();
	virtual void                  InitializeRegisterPacketMsgMethod();
	virtual bool                  InitializeSocket();
	virtual void                  Release();
					              
	virtual void                  BeginConnect();
	virtual void                  EndConnect();
	virtual void                  Disconnect();
	virtual void                  PostDisconnect();

protected:
	virtual class CDDIOCPSession* CreateSession()PURE;

public:
	bool		                  OpenSocket(FIOCPInfo _IOCPInfo);
	bool		                  StartWork(FIOCPThreadInfo _IOCPThreadInfo);
	void		                  StopWork();

	FIOCPThreadInfo               GetCurrentThreadInfo();
	size_t                        GetDefaultReserveSessionSize();
	size_t                        GetDefaultReserveWorkerSize();
	size_t                        GetConnectionNum();
	size_t                        GetReserveSessionNum();
	size_t                        GetRemainReserveSessionSize();

protected:
	void                          _RegisterPacketMsgMethod(TPacketMsg Msg, void (CDDIOCPListener::* Method)(const struct FDDReceivedMsgData*)) { m_PacketMsgMethods[Msg] = Method; }

private:
	void                          ReserveSession(TSessionId Size);
	void                          ReserveWorker(uint16 Size);
	void                          MainWorkThread();

protected:
	std::atomic<TSessionId>       DefaultReserveSessionSize = 2;
	std::atomic<int16>            DefaultReserveWorkerSize = 4;

private:
	std::atomic<FIOCPThreadStatus> m_ThreadStatus;
	std::list<ListenerWorkerPtr>   m_Workers;

	std::map<TSessionId, std::unique_ptr<class CDDIOCPSession, CDDServerBaseObjectDeleter>> m_ReserveSessions;
	TSessionId m_ReserveSessionSize = 0;

	std::map<TPacketMsg, void (CDDIOCPListener::*)(const struct FDDReceivedMsgData*)> m_PacketMsgMethods;

};

#define RegisterPacketMsgMethod(Msg, Method) this->_RegisterPacketMsgMethod(static_cast<TPacketMsg>(Msg), static_cast<void (CDDIOCPListener::*)(const struct FDDReceivedMsgData*)>(Method))