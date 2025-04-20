#include "pch.h"
#include "IOCP/DDSM_IOCPService.h"

#include "IOCP/DDIOCPThreadWorker.h"

#include "DDPacketHeaderAuth.h"
#include "Header/DDServerMainPacketMsg.h"
#include "IOCP/DDSM_IOCPSession.h"
#include "IOCP/DDSM_IOCPListener.h"


CDDSM_IOCPService::CDDSM_IOCPService()
{

}

CDDSM_IOCPService::~CDDSM_IOCPService()
{

}

void CDDSM_IOCPService::Initialize()
{
	Super::Initialize();

}

void CDDSM_IOCPService::InitializeRegisterPacketMsgMethod()
{
	RegisterPacketMsgMethod(EDDPacketAuth::Request_Login_Google, &CDDSM_IOCPService::RecievePacket_Request_Login_Google);

}

CDDIOCPSession* CDDSM_IOCPService::CreateSession()
{
	return new CDDSM_IOCPSession;
}

CDDIOCPThreadWorker* CDDSM_IOCPService::CreateThreadWork()
{
	return new CDDIOCPThreadWorker;
}

CDDIOCPListener* CDDSM_IOCPService::CreateListener()
{
	return new CDDSM_IOCPListener;
}

void CDDSM_IOCPService::Release()
{
	Super::Release();

}

void CDDSM_IOCPService::RecievePacket_Request_Login_Google(const FDDReceivedMsgData* ReceivedMsgData)
{
	const FDDPacketRequestLoginGoogle* pPacket = static_cast<const FDDPacketRequestLoginGoogle*>(ReceivedMsgData->Packet);

	ReceivedMsgData->Session

}
