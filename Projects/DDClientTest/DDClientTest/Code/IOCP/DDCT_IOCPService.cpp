#include "pch.h"
#include "IOCP/DDCT_IOCPService.h"

#include "Header/DDClientTestPacketMsg.h"
#include "IOCP/DDCT_IOCPSession.h"


CDDCT_IOCPService::CDDCT_IOCPService()
{

}

CDDCT_IOCPService::~CDDCT_IOCPService()
{

}

void CDDCT_IOCPService::Initialize()
{
	Super::Initialize();

}

void CDDCT_IOCPService::InitializeRegisterPacketMsgMethod()
{
	RegisterPacketMsgMethod(EPacketMsg::Test, &CDDCT_IOCPService::TestMsg);

}

CDDIOCPSession* CDDCT_IOCPService::CreateSession()
{
	return new CDDCT_IOCPSession;
}

void CDDCT_IOCPService::Release()
{
	Super::Release();

}

void CDDCT_IOCPService::TestMsg(const FDDReceivedMsgData* MsgData)
{
	int iBreakingPoint = 0;
}
