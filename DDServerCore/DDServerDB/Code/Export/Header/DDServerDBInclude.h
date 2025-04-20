#pragma once

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#include <windows.h>

#include "Header/DDServerDBMacro.h"
#include "Header/DDServerDBType.h"
#include "Header/DDServerDBEnum.h"
#include "Header/DDServerDBStruct.h"

#include "DB/DDDBConnectionPool.h"
#include "DB/DDDBConnection.h"
#include "DB/DDDBProcedure.h"
