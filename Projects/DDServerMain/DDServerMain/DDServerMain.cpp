// DDServerMain.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <winsock2.h>
#include <mswsock.h>
#include <windows.h>
#include <thread>

#include "DDServerBase.h"
#include "IOCP/DDSM_IOCPService.h"
#include "Header/DDServerDBInclude.h"
#include "DDPacketHeaderAuth.h"

#include "DB/DDDBConnectionPool.h"
#include "DB/DDDBConnection.h"

#include "DB/DDAuthDBManager.h"


#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")

#define SERVER_PORT 9121
#define BUFFER_SIZE 1024

struct ClientContext {
	SOCKET socket;
	OVERLAPPED overlapped;
	char buffer[BUFFER_SIZE];
};

HANDLE iocpHandle;

// 작업자 스레드 함수
void WorkerThread() {
	DWORD bytesTransferred;
	ULONG_PTR completionKey;
	OVERLAPPED* overlapped;
	FDDPacketRequestLoginGoogle asd;
	while (true) {
		BOOL result = GetQueuedCompletionStatus(
			iocpHandle, &bytesTransferred, &completionKey, &overlapped, INFINITE
		);

		if (!result) {
			std::cerr << "GetQueuedCompletionStatus 실패\n";
			continue;
		}

		// 클라이언트 연결 성공 시 처리
		ClientContext* context = reinterpret_cast<ClientContext*>(completionKey);
		std::cout << "클라이언트 연결 성공!\n";

		// 추가 데이터 처리 로직 (예: 데이터 수신 준비)
	}
}

int main()
{
	DDServerBaseInitialize();

	// StartServer();
	CDDSM_IOCPService ServiceServer;
	ServiceServer.SetServiceInfo(L"0.0.0.0", 9121, 5, 1);
	ServiceServer.Initialize();
	ServiceServer.StartService();

	CDDDBConnectionPool DBManager;
	// bool bConnect = DBManager.Connect(1, TEXT("Driver={SQL Server Native Client 11.0};Server=(localdb)\\MSSQLLocalDB;Database=ServerDB;Trusted_Connection=Yes;"));
	bool bConnect = DBManager.Connect(1, TEXT("SQL Server Native Client 11.0"), TEXT("(localdb)\\MSSQLLocalDB"), TEXT("ServerDB"));
	if (false == bConnect)
	{
		int iBreakingPoint = 0;
	}

	if (false == CDDAuthDBManager::GetInstance()->IsConnected())
	{

	}

	//{		
	//	CDDDBProcedure Procedure = DBManager.GetProcedureInstance(TEXT("rsp_SetGold2"));
	//
	//	Procedure << (int32)1 << (int32)1 << ddb::exec;
	//
	//	int32 ret = -1;
	//	Procedure >> ddb::fetch >> ret;
	//
	//	int iBreakingPoint = 0;
	//}


	while (true)
	{
		std::string input;

		std::cout << "[Server] Enter something (type 'q' to quit): ";
		std::cin >> input;

		if (input == "q")
		{
			std::cout << "Quitting the loop.\n";
			break;
		}

		std::cout << "You entered: " << input << "\n";
	}

	DBManager.Release();
	ServiceServer.Release();

	DDServerBaseRelease();

	return 0;
}