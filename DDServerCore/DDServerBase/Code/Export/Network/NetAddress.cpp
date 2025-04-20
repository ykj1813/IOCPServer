#include "pch.h"
#include "NetAddress.h"
#include <ws2tcpip.h>


FNetAddress::FNetAddress(SOCKADDR_IN _SocketAddress)
	: SocketAddress(_SocketAddress)
{

}

FNetAddress::FNetAddress(const WCHAR* _IP, uint16 _Port)
{
	SocketAddress.sin_family = AF_INET;
	SocketAddress.sin_addr = Ip2Address(_IP);
	SocketAddress.sin_port = ::htons(_Port);
}

const SOCKADDR_IN& FNetAddress::GetSockAddrRaw() const
{
	return SocketAddress;
}

std::wstring FNetAddress::GetIpAddress()
{
	WCHAR buffer[100] = L"";
	::InetNtopW(AF_INET, &SocketAddress.sin_addr, buffer, sizeof(buffer) / sizeof(WCHAR));
	return buffer;
}

uint16 FNetAddress::GetPort()
{
	return ::ntohs(SocketAddress.sin_port);
}

IN_ADDR FNetAddress::Ip2Address(const WCHAR* IP)
{
	IN_ADDR Address;
	::InetPtonW(AF_INET, IP, &Address);
	return Address;
}
