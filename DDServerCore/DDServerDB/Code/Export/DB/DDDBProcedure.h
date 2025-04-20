#pragma once

#include <vector>
#include <tuple>
#include <sqlext.h>

#include "Header/DDServerDBEnum.h"
#include "Header/DDServerDBType.h"
#include "Header/DDServerDBStruct.h"
#include "DB/DDDBConnection.h"


class API_DDSERVERDB_CLASS CDDDBProcedure
{
public:
	CDDDBProcedure(class CDDDBConnectionPool* Owner, const TCHAR* ProcedureName, size_t BindParamNum);
	virtual ~CDDDBProcedure();

public:
	bool         Execute();
	bool         Fetch();

	template<typename T>
	bool BindParameter(T&& Value, SQLLEN* Len = nullptr)
	{
		m_Query += (0 == m_BindingParamNum ? TEXT(" ?") : TEXT(", ?"));

		++m_BindingParamNum;
		bool ret = m_Connection->BindParameter(static_cast<EParamNum>(m_BindingParamNum), &Value, Len);
		return ret;
	}
	template<typename T>
	bool BindParameter(T* Value, size_t Size, SQLLEN* Len = nullptr)
	{
		m_Query += (0 == m_BindingParamNum ? TEXT(" ?") : TEXT(", ?"));

		++m_BindingParamNum;
		bool ret = m_Connection->BindParameter(static_cast<EParamNum>(m_BindingParamNum), Value, Size, Len);
		return ret;
	}

	template<typename T>
	bool BindColumn(T&& Value, SQLLEN* Len = nullptr)
	{		
		++m_BindingColumnNum;
		bool ret = m_Connection->BindColumn(static_cast<EColumnNum>(m_BindingParamNum), &Value, Len);
		return ret;
	}
	template<typename T>
	bool BindColumn(T* Value, size_t Size, SQLLEN* Len = nullptr)
	{
		++m_BindingColumnNum;
		bool ret = m_Connection->BindParameter(static_cast<EColumnNum>(m_BindingParamNum), Value, Size, Len);
		return ret;
	}

	template<typename T>
	bool GetData(T* Value, SQLLEN* Len = nullptr)
	{
		++m_GetDataNum;
		bool ret = m_Connection->GetData(static_cast<EColumnNum>(m_GetDataNum), Value, Len);
		return ret;
	}
	template<typename T>
	bool GetData(T* Value, size_t Size, SQLLEN* Len)
	{
		++m_GetDataNum;
		bool ret = m_Connection->GetData(static_cast<EColumnNum>(m_GetDataNum), Value, Size, Len);
		return ret;
	}

	//:: BindParameter Operator '<<'
	template<typename T, typename = std::enable_if_t<!std::is_function_v<std::remove_pointer_t<std::decay_t<T>>>>>
	CDDDBProcedure& operator<<(T&& Value)
	{
		m_Query += (0 == m_BindingParamNum ? TEXT(" ?") : TEXT(", ?"));
		++m_BindingParamNum;

		m_Connection->BindParameter(static_cast<EParamNum>(m_BindingParamNum), &Value, nullptr);
		return *this;
	}
	template<typename T, typename = std::enable_if_t<!std::is_function_v<std::remove_pointer_t<std::decay_t<T>>>>>
	CDDDBProcedure& operator<<(FDBProcBindPram<T> Parsor)
	{
		m_Query += (0 == m_BindingParamNum ? TEXT(" ?") : TEXT(", ?"));
		++m_BindingParamNum;

		m_Connection->BindParameter(static_cast<EParamNum>(m_BindingParamNum), &Parsor.Value, Parsor.Size, &Parsor.Len);
		return *this;
	}
	template <typename Func, typename = std::enable_if_t<std::is_same_v<Func, decltype(&ddb::exec)>>>
	bool operator<<(Func func)
	{
		return func(*this);
	}

	//:: BindParameter Operator '>>'
	template<typename T, typename = std::enable_if_t<!std::is_function_v<std::remove_pointer_t<std::decay_t<T>>>>>
	CDDDBProcedure& operator>>(T&& Value)
	{
		++m_GetDataNum;

		m_Connection->GetData(static_cast<EColumnNum>(m_GetDataNum), &Value, nullptr);
		return *this;
	}
	template<typename T, typename = std::enable_if_t<!std::is_function_v<std::remove_pointer_t<std::decay_t<T>>>>>
	CDDDBProcedure& operator>>(FDBProcGetData<T> Parsor)
	{
		++m_GetDataNum;

		m_Connection->GetData(static_cast<EColumnNum>(m_GetDataNum), Parsor.Value, Parsor.Size, &Parsor.Len);
		return *this;
	}
	template <typename Func, typename = std::enable_if_t<std::is_same_v<Func, decltype(&ddb::fetch)>>>
	CDDDBProcedure& operator>>(Func func)
	{
		return func(*this);
	}

private:
	class CDDDBConnectionPool* Owner;
	DBConnectionPtr m_Connection;

	std::tstring m_Query;
	bool m_bExecuteSuccess = false;
	bool m_bFetchSuccess = false;

	uint16 m_BindingParamNum = 0;
	uint16 m_BindingColumnNum = 0;
	uint16 m_GetDataNum = 0;
};

namespace ddb
{
	static bool exec(CDDDBProcedure& Procedure)
	{
		return Procedure.Execute();
	}
	static CDDDBProcedure& fetch(CDDDBProcedure& Procedure)
	{
		Procedure.Fetch();
		return Procedure;
	}
};
