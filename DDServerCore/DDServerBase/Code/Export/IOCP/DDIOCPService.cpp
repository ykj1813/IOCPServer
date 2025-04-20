#include "pch.h"
#include "DDIOCPService.h"
#include <format>

#include "Header/DDServerBaseFunction.h"
#include "Base/DDBasePacket.h"
#include "IOCP/DDIOCPSession.h"
#include "IOCP/DDIOCPThreadWorker.h"


CDDIOCPService::CDDIOCPService()
{
	IOCPInfo.NetInfo.NetAddress = FNetAddress(L"127.0.0.1", 7000);
	IOCPInfo.SessionNum         = 1;
	IOCPInfo.WorkerThreadNum    = 1;

	IOCPHandle = INVALID_HANDLE_VALUE;
}

CDDIOCPService::CDDIOCPService(const WCHAR* IP, uint16 Port, uint16 SessionNum, uint8 WorkerThreadNum)
{
	IOCPInfo.NetInfo.NetAddress = FNetAddress(IP, Port);
	IOCPInfo.SessionNum         = SessionNum;
	IOCPInfo.WorkerThreadNum    = WorkerThreadNum;

	IOCPHandle = INVALID_HANDLE_VALUE;
}

CDDIOCPService::~CDDIOCPService()
{

}

void CDDIOCPService::Initialize()
{
	LOCK_GUARD(Mutex);

	InitializeRegisterPacketMsgMethod();
		
}

void CDDIOCPService::InitializeRegisterPacketMsgMethod()
{

}

CDDIOCPSession* CDDIOCPService::CreateSession()
{
	return new CDDIOCPSession;
}

CDDIOCPThreadWorker* CDDIOCPService::CreateThreadWork()
{
	return new CDDIOCPThreadWorker;
}

void CDDIOCPService::Release()
{
	StopService();

}

bool CDDIOCPService::SetServerInfoFromPropertyFile(const TCHAR* FilePath)
{

}

void CDDIOCPService::SetServiceInfo(const WCHAR* IP, uint16 Port, uint16 SessionNum, uint8 WorkerThreadNum)
{
	IOCPInfo.NetInfo.NetAddress = FNetAddress(IP, Port);
	IOCPInfo.SessionNum         = SessionNum;
	IOCPInfo.WorkerThreadNum    = WorkerThreadNum;
}

void CDDIOCPService::SetServiceNetInfo(const WCHAR* IP, uint16 Port)
{
	IOCPInfo.NetInfo.NetAddress = FNetAddress(IP, Port);
}

void CDDIOCPService::SetServiceWorkInfo(uint16 SessionNum, uint8 WorkerThreadNum)
{
	IOCPInfo.SessionNum         = SessionNum;
	IOCPInfo.WorkerThreadNum    = WorkerThreadNum;
}

bool CDDIOCPService::StartService()
{
	//:: Stop
	StopService();

	//:: Setup
	SetupIOCPHandle();

	PreStartService();

	OnStartService();

	PostStartService();


	return true;
}

void CDDIOCPService::StopService()
{
	Sessions.clear();
	m_Works.clear();

}

bool CDDIOCPService::SendPacket(TSessionId SessionId, const FDDBasePacket* Packet)
{
	auto it = Sessions.find(SessionId);
	if (Sessions.end() == it)
	{
		throw std::runtime_error(std::format("Failed Cannot Send Packet : Cannot Find SessionId({})", SessionId));
		return false;
	}

	it->second->SendPacket(Packet);

	return true;
}

void CDDIOCPService::PreStartService()
{

}

void CDDIOCPService::OnStartService()
{
	SetupSession();

	SetupWorker();
}

void CDDIOCPService::PostStartService()
{

}

HANDLE CDDIOCPService::SetupIOCPHandle()
{
	if (INVALID_HANDLE_VALUE != IOCPHandle)
	{
		CloseHandle(IOCPHandle);
	}

	IOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	return IOCPHandle;
}

void CDDIOCPService::SetupSession()
{
	for (TSessionId i = 0; i < IOCPInfo.SessionNum; ++i)
	{
		CDDIOCPSession* NewSession = CreateSession();

		NewSession->SetSessionId(i + 1);
		NewSession->SetIOCP(IOCPHandle);

		NewSession->Initialize();

		NewSession->InitializeOverlapped();

		NewSession->PostInitializeOverlapped();

		NewSession->SetupRecvPacketMethod([&](CDDIOCPSession* Session, const FDDBasePacket* Packet) { this->CallMethodRecvPacketMsg(Session, Packet); });

		Sessions.insert({ NewSession->GetSessionId(), Make_SharedPtr_ServerObject(NewSession) });
	}
}

void CDDIOCPService::SetupWorker()
{
	FIOCPWorkInfo WorkInfo = { IOCPHandle };

	for (size_t i = 0; i < IOCPInfo.WorkerThreadNum; ++i)
	{
		CDDIOCPThreadWorker* Worker = CreateThreadWork();

		Worker->StartWork(&WorkInfo);

		m_Works.push_back(Make_SharedPtr_ServerObject(Worker));
	}
}

void CDDIOCPService::CallMethodRecvPacketMsg(CDDIOCPSession*& Session, const FDDBasePacket*& Packet)
{
	auto it = m_PacketMsgMethods.find(Packet->Header.Id);
	if (m_PacketMsgMethods.end() == it)
	{
		//:: Error
		return;
	}

	FDDReceivedMsgData ReceivedMsgData;
	ReceivedMsgData.Session = Session;
	ReceivedMsgData.Packet  = Packet;
	(this->*(it->second))(&ReceivedMsgData);
}
