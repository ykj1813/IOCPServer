#include "pch.h"
#include "DDIOCPServiceServer.h"

#include "Header/DDServerBaseFunction.h"
#include "IOCP/Server/DDIOCPListener.h"
#include "IOCP/Server/DDIOCPSessionServer.h"


CDDIOCPServiceServer::CDDIOCPServiceServer()
{

}

CDDIOCPServiceServer::CDDIOCPServiceServer(const WCHAR* IP, uint16 Port, uint16 SessionNum, uint8 WorkerThreadNum)
	: CDDIOCPService(IP, Port, SessionNum, WorkerThreadNum)
{

}

CDDIOCPServiceServer::~CDDIOCPServiceServer()
{

}

void CDDIOCPServiceServer::Initialize()
{
	Super::Initialize();

}

void CDDIOCPServiceServer::Release()
{
	Super::Release();

	LOCK_GUARD(Mutex);

}

FDDOverlappedAccept* CDDIOCPServiceServer::CreateOverlappedAccept()
{
	return new FDDOverlappedAccept;
}

CDDIOCPListener* CDDIOCPServiceServer::CreateListener()
{
	return new CDDIOCPListener;
}

CDDIOCPSession* CDDIOCPServiceServer::CreateSession()
{
	return new CDDIOCPSessionServer;
}

void CDDIOCPServiceServer::PreStartService()
{
	Super::PreStartService();

	m_Listener = Make_SharedPtr_ServerObject(CreateListener());

	m_Listener->OpenSocket(IOCPHandle, IOCPInfo.NetInfo);

}

void CDDIOCPServiceServer::OnStartService()
{
	Super::OnStartService();

	for (auto Session : Sessions)
	{
		m_Listener->SetupAcceptEx(std::static_pointer_cast<CDDIOCPSessionServer>(Session.second));
	}

	m_Listener->PostInitializeOverlapped();
}

void CDDIOCPServiceServer::PostStartService()
{
	Super::PostStartService();

}
