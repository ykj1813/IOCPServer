#include "pch.h"
#include "IOCP/Client/DDIOCPServiceClient.h"

#include "IOCP/Client/DDIOCPSessionClient.h"


CDDIOCPServiceClient::CDDIOCPServiceClient()
{

}

CDDIOCPServiceClient::~CDDIOCPServiceClient()
{

}

void CDDIOCPServiceClient::Initialize()
{
	Super::Initialize();

}

void CDDIOCPServiceClient::Release()
{
	Super::Release();

}

bool CDDIOCPServiceClient::SendPacket(const FDDBasePacket* Packet)
{
	return Super::SendPacket(1, Packet);
}

CDDIOCPSession* CDDIOCPServiceClient::CreateSession()
{
	return new CDDIOCPSessionClient;
}

void CDDIOCPServiceClient::PreStartService()
{
	Super::PreStartService();

}

void CDDIOCPServiceClient::OnStartService()
{
	Super::OnStartService();

	for (auto Iter_Session : Sessions)
	{
		Iter_Session.second->SetupConnectEx(&(IOCPInfo.NetInfo.NetAddress));
	}
}

void CDDIOCPServiceClient::PostStartService()
{
	Super::PostStartService();

}
