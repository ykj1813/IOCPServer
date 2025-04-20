#pragma once

#include "Base/DDServerDBObject.h"
#include <sqlext.h>

#include "Header/DDServerDBEnum.h"


class API_DDSERVERDB_CLASS CDDDBConnection : public CDDServerDBObject
{
public:
	CDDDBConnection();
	virtual ~CDDDBConnection();

public:
	virtual void Initialize() override;
	virtual void Release() override;

	bool         Connect(SQLHENV Environment, const TCHAR* ConnectionString);
	void         Clear();

	bool         Execute(const TCHAR* Query);
	bool         Fetch();
	int32        GetRowCount();
	void         Unbind();

	bool         BindParameter(SQLUSMALLINT ParamIndex, SQLSMALLINT CType, SQLSMALLINT SqlType, SQLULEN Len, SQLPOINTER Ptr, SQLLEN* Index);
	bool         BindParameter(EParamNum ParamIndex, bool*   Value, SQLLEN* Index);
	bool         BindParameter(EParamNum ParamIndex, int8*   Value, SQLLEN* Index);
	bool         BindParameter(EParamNum ParamIndex, int16*  Value, SQLLEN* Index);
	bool         BindParameter(EParamNum ParamIndex, int32*  Value, SQLLEN* Index);
	bool         BindParameter(EParamNum ParamIndex, float*  Value, SQLLEN* Index);
	bool         BindParameter(EParamNum ParamIndex, int64*  Value, SQLLEN* Index);
	bool         BindParameter(EParamNum ParamIndex, double* Value, SQLLEN* Index);	
	bool         BindParameter(EParamNum ParamIndex, const WCHAR* String, SQLLEN* Index);
	bool         BindParameter(EParamNum ParamIndex, const char* String, SQLLEN* Index);
	bool         BindParameter(EParamNum ParamIndex, const BYTE* Values, size_t Size, SQLLEN* Index);
	bool         BindParameter(EParamNum ParamIndex, TIMESTAMP_STRUCT* Value, SQLLEN* Index);

	bool         BindColumn(SQLUSMALLINT ColumnIndex, SQLSMALLINT CType, SQLULEN Len, SQLPOINTER Value, SQLLEN* Index);
	bool         BindColumn(EColumnNum ColumnIndex, bool*   Value, SQLLEN* Index);
	bool         BindColumn(EColumnNum ColumnIndex, int8*   Value, SQLLEN* Index);
	bool         BindColumn(EColumnNum ColumnIndex, int16*  Value, SQLLEN* Index);
	bool         BindColumn(EColumnNum ColumnIndex, int32*  Value, SQLLEN* Index);
	bool         BindColumn(EColumnNum ColumnIndex, float*  Value, SQLLEN* Index);
	bool         BindColumn(EColumnNum ColumnIndex, int64*  Value, SQLLEN* Index);
	bool         BindColumn(EColumnNum ColumnIndex, double* Value, SQLLEN* Index);
	bool         BindColumn(EColumnNum ColumnIndex, WCHAR* String, size_t Size, SQLLEN* Index);
	bool         BindColumn(EColumnNum ColumnIndex, char* String, size_t Size, SQLLEN* Index);
	bool         BindColumn(EColumnNum ColumnIndex, BYTE* Values, size_t Size, SQLLEN* Index);
	bool         BindColumn(EColumnNum ColumnIndex, TIMESTAMP_STRUCT* Value, SQLLEN* Index);
	
	bool         GetData(SQLUSMALLINT ColumnIndex, SQLSMALLINT CType, SQLULEN Len, SQLPOINTER Value, SQLLEN* Index);
	bool         GetData(EColumnNum ColumnIndex, bool* Value, SQLLEN* Index);
	bool         GetData(EColumnNum ColumnIndex, int8* Value, SQLLEN* Index);
	bool         GetData(EColumnNum ColumnIndex, int16* Value, SQLLEN* Index);
	bool         GetData(EColumnNum ColumnIndex, int32* Value, SQLLEN* Index);
	bool         GetData(EColumnNum ColumnIndex, float* Value, SQLLEN* Index);
	bool         GetData(EColumnNum ColumnIndex, int64* Value, SQLLEN* Index);
	bool         GetData(EColumnNum ColumnIndex, double* Value, SQLLEN* Index);
	bool         GetData(EColumnNum ColumnIndex, WCHAR* String, size_t Size, SQLLEN* Index);
	bool         GetData(EColumnNum ColumnIndex, char* String, size_t Size, SQLLEN* Index);
	bool         GetData(EColumnNum ColumnIndex, BYTE* Values, size_t Size, SQLLEN* Index);
	bool         GetData(EColumnNum ColumnIndex, TIMESTAMP_STRUCT* Value, SQLLEN* Index);

private:
	void         HandleError(SQLRETURN Ret);

public:
	SQLHDBC	     m_Connection = SQL_NULL_HANDLE;
	SQLHSTMT     m_Statement = SQL_NULL_HANDLE;

};
