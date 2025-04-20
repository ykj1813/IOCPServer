#pragma once

#include "Base/DDServerBaseObject.h"
#include <map>
#include <list>

#include "Header/DDServerBaseType.h"
#include "Header/DDServerBaseStruct.h"


class API_DDSERVERBASE_CLASS CDDIOCPService : public CDDServerBaseObject
{
public:
	CDDIOCPService();
	CDDIOCPService(const WCHAR* IP, uint16 Port, uint16 SessionNum, uint8 WorkerThreadNum);
	virtual ~CDDIOCPService();

public:
	virtual void                  Initialize() override;
	virtual void                  Release() override;

	bool                          SetServerInfoFromPropertyFile(const TCHAR* FilePath);
	void                          SetServiceInfo(const WCHAR* IP, uint16 Port, uint16 SessionNum, uint8 WorkerThreadNum);
	void                          SetServiceNetInfo(const WCHAR* IP, uint16 Port);
	void                          SetServiceWorkInfo(uint16 SessionNum, uint8 WorkerThreadNum);
	bool                          StartService();
	void                          StopService();

	bool                          SendPacket(TSessionId SessionId, const struct FDDBasePacket* Packet);

protected:
	virtual void                  InitializeRegisterPacketMsgMethod();
	virtual class CDDIOCPSession* CreateSession();
	virtual class CDDIOCPThreadWorker* CreateThreadWork();

	virtual void                  PreStartService();
	virtual void                  OnStartService();
	virtual void                  PostStartService();

protected:
	void                          _RegisterPacketMsgMethod(TPacketMsg Msg, void (CDDIOCPService::* Method)(const struct FDDReceivedMsgData*)) { m_PacketMsgMethods[Msg] = Method; }

private:
	HANDLE                        SetupIOCPHandle();
	void	                      SetupSession();
	void                          SetupWorker();
	void                          CallMethodRecvPacketMsg(class CDDIOCPSession*& Session, const struct FDDBasePacket*& Packet);

protected:
	FIOCPInfo                        IOCPInfo;
	HANDLE                           IOCPHandle;
	std::map<TSessionId, SessionPtr> Sessions;

private:
	std::list<ThreadWorkerPtr>       m_Works;

	std::map<TPacketMsg, void (CDDIOCPService::*)(const struct FDDReceivedMsgData*)> m_PacketMsgMethods;
};

#define RegisterPacketMsgMethod(Msg, Method) this->_RegisterPacketMsgMethod(static_cast<TPacketMsg>(Msg), static_cast<void (CDDIOCPService::*)(const struct FDDReceivedMsgData*)>(Method))