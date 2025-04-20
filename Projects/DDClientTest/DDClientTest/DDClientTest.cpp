// DDClientTest.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include <iostream>

#include "Base/DDBasePacket.h"
#include "DDServerBase.h"

#include "Header/DDClientTestPacketMsg.h"
#include "IOCP/DDCT_IOCPService.h"


#pragma comment(lib, "Ws2_32.lib")

#define SERVER_IP "127.0.0.1"  // 서버 IP 주소
#define SERVER_PORT 9121       // 서버 포트 번호
#define BUFFER_SIZE 1024       // 버퍼 크기


#pragma pack(push, 1) //:: 1바이트 정렬

struct FDDTestPacket : public FDDBasePacket
{
	FDDTestPacket()
		: FDDBasePacket((TPacketId)EPacketMsg::Test, sizeof(FDDTestPacket))
		, szData("")
	{
		
	}

	FDDPacketRawHeader Header;

	char szData[128];
};

#pragma pack(pop) //:: 1바이트 정렬


int main()
{
	DDServerBaseInitialize();

	CDDCT_IOCPService ServiceClient;
	ServiceClient.SetServiceInfo(L"127.0.0.1", 9121, 1, 1);
	ServiceClient.Initialize();
	ServiceClient.StartService();

	while (true)
	{
		std::string input;

		std::cout << "[Client] Enter something (type 'q' to quit): ";
		std::cin >> input;

		if (input == "q")
		{
			std::cout << "Quitting the loop.\n";
			break;
		}
		else
		{
			FDDTestPacket Packet;
			strcpy_s(Packet.szData, input.c_str());
			ServiceClient.SendPacket(&Packet);

			std::cout << "SendMessage.\n";
		}
	}


	DDServerBaseRelease();

	return 0;

}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
