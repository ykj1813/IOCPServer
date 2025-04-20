#pragma once

#include <winsock2.h>
#include <string>


class FNetAddress
{
public:
	FNetAddress() = default;
	FNetAddress(SOCKADDR_IN _SocketAddress);
	FNetAddress(const WCHAR* _IP, uint16 _Port);

	const SOCKADDR_IN&  GetSockAddrRaw() const;
	std::wstring        GetIpAddress();
	uint16              GetPort();

public:
	static IN_ADDR	Ip2Address(const WCHAR* IP);

private:
	SOCKADDR_IN		SocketAddress = { 0, };
};

