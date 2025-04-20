#include "pch.h"
#include "DB/DDDBConnectionPool.h"

#include <format>
#include <sql.h>
#include <sqlext.h>

#include "Header/DDServerDBFunction.h"
#include "DB/DDDBConnection.h"
#include "DB/DDDBProcedure.h"


CDDDBConnectionPool::CDDDBConnectionPool()
{

}

CDDDBConnectionPool::~CDDDBConnectionPool()
{

}

void CDDDBConnectionPool::Initialize()
{
	Release();

}

void CDDDBConnectionPool::Release()
{
	Clear();
}

bool CDDDBConnectionPool::Connect(int32 ConnectionCount, const TCHAR* DeviceName, const TCHAR* ServerName, const TCHAR* DBName)
{
	std::tstring strConnection = TEXT("");
	strConnection += std::format(TEXT("Driver={{{}}};"), DeviceName);
	strConnection += std::format(TEXT("Server={};"), ServerName);
	strConnection += std::format(TEXT("Database={};"), DBName);
	strConnection += std::format(TEXT("Trusted_Connection={};"), TEXT("Yes"));

	m_DBName = DBName;

	return Connect(ConnectionCount, strConnection.c_str());
}

bool CDDDBConnectionPool::Connect(int32 ConnectionCount, const TCHAR* ConnectionString)
{
	LOCK_GUARD(Mutex);

	if (SQL_SUCCESS != ::SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_Environment))
	{
		return false;
	}

	if (SQL_SUCCESS != ::SQLSetEnvAttr(m_Environment, SQL_ATTR_ODBC_VERSION, reinterpret_cast<SQLPOINTER>(SQL_OV_ODBC3), 0))
	{
		return false;
	}

	std::tstring strConnection = ConnectionString;


	for (int32 i = 0; i < ConnectionCount; i++)
	{
		DBConnectionPtr Connection = Make_SharedPtr_DBObject(CreateConnection());
		if (false == Connection->Connect(m_Environment, strConnection.c_str()))
		{
			return false;
		}

		m_Connections.push_back(Connection);
	}

	return true;
}

SQLHENV CDDDBConnectionPool::GetEnvironment()
{
	LOCK_SHARED(Mutex);

	return m_Environment;
}

void CDDDBConnectionPool::Clear()
{
	LOCK_GUARD(Mutex);

	if (SQL_NULL_HANDLE != m_Environment)
	{
		::SQLFreeHandle(SQL_HANDLE_ENV, m_Environment);
		m_Environment = SQL_NULL_HANDLE;
	}

	m_Connections.clear();
}

DBConnectionPtr CDDDBConnectionPool::Pop_Back()
{
	LOCK_GUARD(Mutex);

	if (m_Connections.empty())
	{
		return nullptr;
	}

	DBConnectionPtr Connection = m_Connections.back();
	m_Connections.pop_back();

	return Connection;
}

void CDDDBConnectionPool::Push_Back(DBConnectionPtr Connection)
{
	if (nullptr == Connection)
	{
		return;
	}

	LOCK_GUARD(Mutex);

	m_Connections.push_back(Connection);
}

size_t CDDDBConnectionPool::Size()
{
	LOCK_SHARED(Mutex);

	return m_Connections.size();
}

const TCHAR* CDDDBConnectionPool::GetDBName()
{
	LOCK_SHARED(Mutex);

	return m_DBName.c_str();
}

CDDDBProcedure CDDDBConnectionPool::GetProcedureInstance(const TCHAR* ProcedureName, size_t ParamNum /*= 0*/)
{
	return CDDDBProcedure(this, ProcedureName, ParamNum);
}

CDDDBConnection* CDDDBConnectionPool::CreateConnection()
{
	return new CDDDBConnection;
}
