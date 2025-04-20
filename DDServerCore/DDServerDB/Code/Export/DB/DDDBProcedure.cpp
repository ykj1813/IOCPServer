#include "pch.h"
#include "DB/DDDBProcedure.h"

#include <iostream>
#include <string>
#include <format>
#include <tchar.h>
#include <sql.h>

#include "DB/DDDBConnectionPool.h"


CDDDBProcedure::CDDDBProcedure(class CDDDBConnectionPool* Owner, const TCHAR* ProcedureName, size_t BindParamNum)
{
	this->Owner = Owner;
	m_Connection = Owner->Pop_Back();
	m_Query = std::format(TEXT("EXEC {}.dbo.{}"), Owner->GetDBName(), ProcedureName);
	// m_Query = std::format(TEXT("EXEC dbo.{}"), ProcedureName);	
	m_Connection->Unbind();
}

CDDDBProcedure::~CDDDBProcedure()
{
	if (nullptr != Owner && nullptr != m_Connection)
	{
		Owner->Push_Back(std::move(m_Connection));

		m_Connection = nullptr;
		Owner = nullptr;
	}
}

bool CDDDBProcedure::Execute()
{
	m_Query += (0 == m_BindingParamNum ? TEXT("") : TEXT(""));
	return m_bExecuteSuccess = m_Connection->Execute(m_Query.c_str());
}

bool CDDDBProcedure::Fetch()
{
	m_GetDataNum = 0;
	return m_bFetchSuccess = m_Connection->Fetch();
}
