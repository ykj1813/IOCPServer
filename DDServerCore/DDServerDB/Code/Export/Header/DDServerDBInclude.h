#pragma once

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#include <windows.h>

#include "Header/DDServerDBMacro.h"
#include "Header/DDServerDBType.h"
#include "Header/DDServerDBEnum.h"
#include "Header/DDServerDBStruct.h"

#include "DB/DDDBConnectionPool.h"
#include "DB/DDDBConnection.h"
#include "DB/DDDBProcedure.h"
