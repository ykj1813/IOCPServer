#pragma once

#include "Base/DDServerDBObject.h"

#include <sqlext.h>
#include <vector>

#include "Header/DDServerDBType.h"


class API_DDSERVERDB_CLASS CDDDBConnectionPool : public CDDServerDBObject
{
public:
	CDDDBConnectionPool();
	virtual ~CDDDBConnectionPool();

public:
	virtual void            Initialize() override;
	virtual void            Release() override;

	bool                    Connect(int32 ConnectionCount, const TCHAR* DeviceName, const TCHAR* ServerName, const TCHAR* DBName);
	bool                    Connect(int32 ConnectionCount, const TCHAR* ConnectionString);
	SQLHENV                 GetEnvironment();
	void                    Clear();

	DBConnectionPtr         Pop_Back();
	void                    Push_Back(DBConnectionPtr Connection);
	size_t                  Size();

	const TCHAR*            GetDBName();
	CDDDBProcedure          GetProcedureInstance(const TCHAR* ProcedureName, size_t ParamNum = 0);

protected:
	virtual class CDDDBConnection* CreateConnection();

private:
	std::tstring                    m_DBName;
	SQLHENV                         m_Environment = SQL_NULL_HANDLE;
	std::vector<DBConnectionPtr>	m_Connections;

};
