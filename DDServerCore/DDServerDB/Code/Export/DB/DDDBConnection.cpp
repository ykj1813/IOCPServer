#include "pch.h"
#include "DB/DDDBConnection.h"

#include <iostream>
#include <string>
#include <tchar.h>
#include <sql.h>


CDDDBConnection::CDDDBConnection()
{

}

CDDDBConnection::~CDDDBConnection()
{

}

void CDDDBConnection::Initialize()
{
	Release();

	m_Connection = SQL_NULL_HANDLE;
	m_Statement  = SQL_NULL_HANDLE;
}

void CDDDBConnection::Release()
{
	Clear();
}

bool CDDDBConnection::Connect(SQLHENV Environment, const TCHAR* ConnectionString)
{
	if (SQL_SUCCESS != ::SQLAllocHandle(SQL_HANDLE_DBC, Environment, &m_Connection))
	{
		return false;
	}

	TCHAR StringBuffer[MAX_PATH] = TEXT("");
	_tcscpy_s(StringBuffer, ConnectionString);

	TCHAR ResultString[MAX_PATH] = TEXT("");
	SQLSMALLINT ResultStringLen = 0;

	SQLRETURN ret = ::SQLDriverConnect(
		m_Connection, NULL,
		reinterpret_cast<SQLTCHAR*>(StringBuffer), _countof(StringBuffer),
		reinterpret_cast<SQLTCHAR*>(ResultString), _countof(ResultString), &ResultStringLen,
		SQL_DRIVER_NOPROMPT
	);

	if (SQL_SUCCESS != ret && SQL_SUCCESS_WITH_INFO != ret)
	{
		HandleError(ret);
		return false;
	}

	if (SQL_SUCCESS != ::SQLAllocHandle(SQL_HANDLE_STMT, m_Connection, &m_Statement))
	{
		return false;
	}

	return true;
}

void CDDDBConnection::Clear()
{
	if (SQL_NULL_HANDLE != m_Connection)
	{
		::SQLFreeHandle(SQL_HANDLE_DBC, m_Connection);
		m_Connection = SQL_NULL_HANDLE;
	}

	if (SQL_NULL_HANDLE != m_Statement)
	{
		::SQLFreeHandle(SQL_HANDLE_STMT, m_Statement);
		m_Statement = SQL_NULL_HANDLE;
	}
}

bool CDDDBConnection::Execute(const TCHAR* Query)
{
	if (SQL_NULL_HANDLE == m_Statement)
	{
		return false;
	}

	SQLRETURN ret = ::SQLExecDirect(m_Statement, (SQLTCHAR*)Query, SQL_NTSL);
	if (SQL_SUCCESS != ret && SQL_SUCCESS_WITH_INFO != ret)
	{
		HandleError(ret);
		return false;
	}

	return true;
}

bool CDDDBConnection::Fetch()
{
	if (SQL_NULL_HANDLE == m_Statement)
	{
		return false;
	}

	SQLRETURN ret = ::SQLFetch(m_Statement);

	if (SQL_NO_DATA == ret)
	{
		HandleError(ret);
		return false;
	}

	if (SQL_ERROR == ret)
	{
		HandleError(ret);
		return false;
	}

	if (SQL_SUCCESS == ret || SQL_SUCCESS_WITH_INFO == ret)
	{
		return true;
	}

	return true;
}

int32 CDDDBConnection::GetRowCount()
{
	if (SQL_NULL_HANDLE == m_Statement)
	{
		return -1;
	}

	SQLLEN RowCount = 0;
	SQLRETURN ret = ::SQLRowCount(m_Statement, &RowCount);

	if (SQL_SUCCESS != ret && SQL_SUCCESS_WITH_INFO != ret)
	{
		HandleError(ret);
		return -1;
	}

	return CAST_INT32(RowCount);
}

bool CDDDBConnection::BindParameter(SQLUSMALLINT ParamIndex, SQLSMALLINT CType, SQLSMALLINT SqlType, SQLULEN Len, SQLPOINTER Ptr, SQLLEN* Index)
{
	if (SQL_NULL_HANDLE == m_Statement)
	{
		return false;
	}

	SQLRETURN ret = ::SQLBindParameter(m_Statement, ParamIndex, SQL_PARAM_INPUT, CType, SqlType, Len, 0, Ptr, 0, Index);
	if (SQL_SUCCESS != ret && SQL_SUCCESS_WITH_INFO != ret)
	{
		HandleError(ret);
		return false;
	}

	return true;
}

bool CDDDBConnection::BindParameter(EParamNum ParamIndex, bool* Value, SQLLEN* Index)
{
	return BindParameter(static_cast<SQLUSMALLINT>(ParamIndex), SQL_C_TINYINT, SQL_TINYINT, sizeof(bool), Value, Index);
}

bool CDDDBConnection::BindParameter(EParamNum ParamIndex, int8* Value, SQLLEN* Index)
{
	return BindParameter(static_cast<SQLUSMALLINT>(ParamIndex), SQL_C_TINYINT, SQL_TINYINT, sizeof(int8), Value, Index);
}

bool CDDDBConnection::BindParameter(EParamNum ParamIndex, int16* Value, SQLLEN* Index)
{
	return BindParameter(static_cast<SQLUSMALLINT>(ParamIndex), SQL_C_SHORT, SQL_SMALLINT, sizeof(int16), Value, Index);
}

bool CDDDBConnection::BindParameter(EParamNum ParamIndex, int32* Value, SQLLEN* Index)
{
	return BindParameter(static_cast<SQLUSMALLINT>(ParamIndex), SQL_C_LONG, SQL_INTEGER, sizeof(int32), Value, Index);
}

bool CDDDBConnection::BindParameter(EParamNum ParamIndex, float* Value, SQLLEN* Index)
{
	return BindParameter(static_cast<SQLUSMALLINT>(ParamIndex), SQL_C_FLOAT, SQL_REAL, sizeof(float), Value, Index);
}

bool CDDDBConnection::BindParameter(EParamNum ParamIndex, int64* Value, SQLLEN* Index)
{
	return BindParameter(static_cast<SQLUSMALLINT>(ParamIndex), SQL_C_SBIGINT, SQL_BIGINT, sizeof(int64), Value, Index);
}

bool CDDDBConnection::BindParameter(EParamNum ParamIndex, double* Value, SQLLEN* Index)
{
	return BindParameter(static_cast<SQLUSMALLINT>(ParamIndex), SQL_C_DOUBLE, SQL_DOUBLE, sizeof(double), Value, Index);
}

bool CDDDBConnection::BindParameter(EParamNum ParamIndex, const WCHAR* String, SQLLEN* Index)
{
	if (nullptr == String)
	{
		if (nullptr != Index)
		{
			*Index = SQL_NULL_DATA;
		}
		return false;
	}
	SQLULEN Size = static_cast<SQLULEN>((::wcslen(String) + 1) * 2);
	if (nullptr != Index)
	{
		*Index = SQL_NTSL;
	}
	SQLSMALLINT SqlType = 4000 < Size ? SQL_WLONGVARCHAR : SQL_WVARCHAR;

	return BindParameter(static_cast<SQLUSMALLINT>(ParamIndex), SQL_C_WCHAR, SqlType, Size, (SQLPOINTER)String, Index);
}

bool CDDDBConnection::BindParameter(EParamNum ParamIndex, const char* String, SQLLEN* Index)
{
	if (nullptr == String)
	{
		if (nullptr != Index)
		{
			*Index = SQL_NULL_DATA;
		}
		return false;
	}
	SQLULEN Size = static_cast<SQLULEN>((::strlen(String) + 1));
	if (nullptr != Index)
	{
		*Index = SQL_NTSL;
	}
	SQLSMALLINT SqlType = 2000 < Size ? SQL_LONGVARCHAR : SQL_VARCHAR;

	return BindParameter(static_cast<SQLUSMALLINT>(ParamIndex), SQL_C_WCHAR, SqlType, Size, (SQLPOINTER)String, Index);
}

bool CDDDBConnection::BindParameter(EParamNum ParamIndex, const BYTE* Values, size_t Size, SQLLEN* Index)
{
	if (Values == nullptr)
	{
		*Index = SQL_NULL_DATA;
		Size = 1;
	}
	else
	{
		*Index = Size;
	}

	SQLSMALLINT SqlType = 8000 < Size ? SQL_LONGVARBINARY : SQL_BINARY;

	return BindParameter(static_cast<SQLUSMALLINT>(ParamIndex), SQL_C_BINARY, SQL_LONGVARBINARY, Size, (BYTE*)Values, Index);
}

bool CDDDBConnection::BindParameter(EParamNum ParamIndex, TIMESTAMP_STRUCT* Value, SQLLEN* Index)
{
	return BindParameter(static_cast<SQLUSMALLINT>(ParamIndex), SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, sizeof(TIMESTAMP_STRUCT), Value, Index);
}

bool CDDDBConnection::BindColumn(SQLUSMALLINT ColumnIndex, SQLSMALLINT CType, SQLULEN Len, SQLPOINTER Value, SQLLEN* Index)
{
	SQLRETURN ret = ::SQLBindCol(m_Statement, ColumnIndex, CType, Value, Len, Index);
	if (SQL_SUCCESS != ret && SQL_SUCCESS_WITH_INFO != ret)
	{
		HandleError(ret);
		return false;
	}

	return true;
}

bool CDDDBConnection::BindColumn(EColumnNum ColumnIndex, bool* Value, SQLLEN* Index)
{
	return BindColumn(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_TINYINT, sizeof(bool), Value, Index);
}

bool CDDDBConnection::BindColumn(EColumnNum ColumnIndex, int8* Value, SQLLEN* Index)
{
	return BindColumn(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_TINYINT, sizeof(int8), Value, Index);
}

bool CDDDBConnection::BindColumn(EColumnNum ColumnIndex, int16* Value, SQLLEN* Index)
{
	return BindColumn(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_SHORT, sizeof(int16), Value, Index);
}

bool CDDDBConnection::BindColumn(EColumnNum ColumnIndex, int32* Value, SQLLEN* Index)
{
	return BindColumn(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_LONG, sizeof(int32), Value, Index);
}

bool CDDDBConnection::BindColumn(EColumnNum ColumnIndex, float* Value, SQLLEN* Index)
{
	return BindColumn(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_FLOAT, sizeof(float), Value, Index);
}

bool CDDDBConnection::BindColumn(EColumnNum ColumnIndex, int64* Value, SQLLEN* Index)
{
	return BindColumn(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_SBIGINT, sizeof(int64), Value, Index);
}

bool CDDDBConnection::BindColumn(EColumnNum ColumnIndex, double* Value, SQLLEN* Index)
{
	return BindColumn(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_DOUBLE, sizeof(double), Value, Index);
}

bool CDDDBConnection::BindColumn(EColumnNum ColumnIndex, char* String, size_t Size, SQLLEN* Index)
{
	return BindColumn(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_CHAR, Size, String, Index);
}

bool CDDDBConnection::BindColumn(EColumnNum ColumnIndex, WCHAR* String, size_t Size, SQLLEN* Index)
{
	return BindColumn(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_WCHAR, Size, String, Index);
}

bool CDDDBConnection::BindColumn(EColumnNum ColumnIndex, BYTE* Values, size_t Size, SQLLEN* Index)
{
	return BindColumn(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_BINARY, Size, Values, Index);
}

bool CDDDBConnection::BindColumn(EColumnNum ColumnIndex, TIMESTAMP_STRUCT* Value, SQLLEN* Index)
{
	return BindColumn(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_TYPE_TIMESTAMP, sizeof(TIMESTAMP_STRUCT), Value, Index);
}

bool CDDDBConnection::GetData(SQLUSMALLINT ColumnIndex, SQLSMALLINT CType, SQLULEN Len, SQLPOINTER Value, SQLLEN* Index)
{
	SQLRETURN ret = ::SQLGetData(m_Statement, ColumnIndex, CType, Value, Len, Index);
	if (SQL_SUCCESS != ret && SQL_SUCCESS_WITH_INFO != ret)
	{
		HandleError(ret);
		return false;
	}

	return true;	
}

bool CDDDBConnection::GetData(EColumnNum ColumnIndex, bool* Value, SQLLEN* Index)
{
	return GetData(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_TINYINT, sizeof(bool), Value, Index);
}

bool CDDDBConnection::GetData(EColumnNum ColumnIndex, int8* Value, SQLLEN* Index)
{
	return GetData(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_TINYINT, sizeof(int8), Value, Index);
}

bool CDDDBConnection::GetData(EColumnNum ColumnIndex, int16* Value, SQLLEN* Index)
{
	return GetData(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_SHORT, sizeof(int16), Value, Index);
}

bool CDDDBConnection::GetData(EColumnNum ColumnIndex, int32* Value, SQLLEN* Index)
{
	return GetData(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_LONG, sizeof(int32), Value, Index);
}

bool CDDDBConnection::GetData(EColumnNum ColumnIndex, float* Value, SQLLEN* Index)
{
	return GetData(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_FLOAT, sizeof(float), Value, Index);
}

bool CDDDBConnection::GetData(EColumnNum ColumnIndex, int64* Value, SQLLEN* Index)
{
	return GetData(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_SBIGINT, sizeof(int64), Value, Index);
}

bool CDDDBConnection::GetData(EColumnNum ColumnIndex, double* Value, SQLLEN* Index)
{
	return GetData(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_DOUBLE, sizeof(double), Value, Index);
}

bool CDDDBConnection::GetData(EColumnNum ColumnIndex, char* String, size_t Size, SQLLEN* Index)
{
	return GetData(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_CHAR, Size, String, Index);
}

bool CDDDBConnection::GetData(EColumnNum ColumnIndex, WCHAR* String, size_t Size, SQLLEN* Index)
{
	return GetData(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_WCHAR, Size, String, Index);
}

bool CDDDBConnection::GetData(EColumnNum ColumnIndex, BYTE* Values, size_t Size, SQLLEN* Index)
{
	return GetData(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_BINARY, Size, Values, Index);
}

bool CDDDBConnection::GetData(EColumnNum ColumnIndex, TIMESTAMP_STRUCT* Value, SQLLEN* Index)
{
	return GetData(static_cast<SQLUSMALLINT>(ColumnIndex), SQL_C_TYPE_TIMESTAMP, sizeof(TIMESTAMP_STRUCT), Value, Index);
}

void CDDDBConnection::Unbind()
{
	if (SQL_NULL_HANDLE == m_Statement)
	{
		return;
	}

	::SQLFreeStmt(m_Statement, SQL_UNBIND      );
	::SQLFreeStmt(m_Statement, SQL_RESET_PARAMS);
	::SQLFreeStmt(m_Statement, SQL_CLOSE       );
}

void CDDDBConnection::HandleError(SQLRETURN ret)
{
	if (SQL_SUCCESS == ret)
	{
		return;
	}

	if (SQL_NULL_HANDLE == m_Statement)
	{
		return;
	}

	SQLSMALLINT RecNumber = 1;
	SQLTCHAR Sqlstate[MAX_PATH] = TEXT("");
	SQLINTEGER NativeError = 0;
	SQLTCHAR MessageText[MAX_PATH] = TEXT("");
	SQLSMALLINT TextLength = 0;
	SQLRETURN ErrorRet = 0;

	while (true)
	{
		ErrorRet = ::SQLGetDiagRec(
			SQL_HANDLE_STMT,
			m_Statement,
			RecNumber,
			Sqlstate,
			&NativeError,
			MessageText, _countof(MessageText), &TextLength
		);

		if (SQL_NO_DATA == ErrorRet)
		{
			break;
		}

		if (ErrorRet != SQL_SUCCESS && ErrorRet != SQL_SUCCESS_WITH_INFO)
		{
			break;
		}

		//:: TODO : Logging
		std::tout.imbue(std::locale("kor"));
		std::tout << TEXT("[") << RecNumber << TEXT("]") << MessageText << std::endl;

		++RecNumber;
	}

}
