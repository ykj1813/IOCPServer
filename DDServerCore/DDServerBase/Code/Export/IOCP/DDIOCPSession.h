#pragma once

#include "IOCP/DDIOCPObject.h"
#include <map>
#include <functional>

#include "Header/DDServerBaseType.h"
#include "Network/NetAddress.h"
#include "Network/NetBuffer.h"


class API_DDSERVERBASE_CLASS CDDIOCPSession : public CDDIOCPObject
{
public:
	CDDIOCPSession();
	virtual ~CDDIOCPSession();

public:
	virtual void                      Initialize() override;
	virtual bool                      InitializeSocket() override;
	virtual void                      InitializeOverlapped() override;
	virtual void                      PostInitializeOverlapped() override;
	virtual void                      PreConnect() override;
	virtual void                      OnConnect() override;
	virtual void                      PostConnect() override;
	virtual void                      OnDisconnect() override;
	virtual void                      PostDisconnect() override;
	virtual void                      Release() override;

	void                              SetupRecvPacketMethod(std::function<void(class CDDIOCPSession*, const struct FDDBasePacket*)> RecvFunction);
	bool                              SetupAcceptEx(SOCKET ListenSocket, DDOverlappedAcceptPtr OverlappedAccept);
	bool                              SetupConnectEx(const class FNetAddress* NetAddress);
	bool                              SetupDisconnectEx();
	bool                              SetupWSASend();
	bool                              SetupWSARecv(TSocketError* OUT ErrorCode = nullptr);

	bool                              SendPacket(const struct FDDBasePacket* Packet);

protected:
	virtual void                      Dispatch(struct FDDOverlapped* Overlapped, const DWORD& BytesTransferred) override;

	virtual DDOverlappedConnectPtr    CreateOverlappedConnect() const;
	virtual size_t                    GetOverlappedConnectSize() const;
	virtual DDOverlappedDisconnectPtr CreateOverlappedDisconnect() const;
	virtual size_t                    GetOverlappedDisconnectSize() const;
	virtual DDOverlappedSendPtr       CreateOverlappedSend() const;
	virtual size_t                    GetOverlappedSendSize() const;
	virtual DDOverlappedRecvPtr       CreateOverlappedRecv() const;
	virtual size_t                    GetOverlappedRecvSize() const;

public:
	void                              SetIOCP(HANDLE _IOCPHandle);
	void                              SetNetAddress(FNetAddress NetAddress);
							          
	void                              Stop();
							          
	void                              SetSessionId(TSessionId SessionId);
	TSessionId                        GetSessionId() const;

private:
	void                              OnProcessConnect();
	void                              OnProcessDisconnect();
	bool                              OnProcessRecvPacket(struct FDDOverlappedRecv* OverlappedRecv, const DWORD& BytesTransferred);
	void                              OnProcessSendPacket(struct FDDOverlappedSend* OverlappedSend, const DWORD& BytesTransferred);

private:
	TSessionId               m_ConnectionId;
	FNetAddress              m_NetAddress;

	SOCKET                   ListenSocket;
	DDOverlappedAcceptPtr    OverlappedAcceptPtr;
	FDDSessionOverlapped     Overlappeds;
	FNetBuffer               RecvBuffer, PendingRecvBuffer;
	FNetBuffer               SendBuffer;
	std::function<void(class CDDIOCPSession*, const struct FDDBasePacket*)> m_RecvPacketFunction;

};

