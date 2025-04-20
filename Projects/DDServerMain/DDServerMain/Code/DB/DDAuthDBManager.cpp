#include "pch.h"
#include "DB/DDAuthDBManager.h"


CDDAuthDBManager::CDDAuthDBManager()
{

}

CDDAuthDBManager::~CDDAuthDBManager()
{

}

void CDDAuthDBManager::Initialize()
{
	Connect(5, TEXT("SQL Server Native Client 11.0"), TEXT("(localdb)\\MSSQLLocalDB"), TEXT("AccountDB"));
}

void CDDAuthDBManager::Release()
{
	Disconnect();
}
