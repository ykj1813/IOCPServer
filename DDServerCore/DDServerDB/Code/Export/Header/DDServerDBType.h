#pragma once

#include "Header/DDCommonType.h"
#include "Base/DDServerDBObject.h"


//:: Using SharedPtr
using DBConnectionPoolPtr = std::shared_ptr<class CDDDBConnectionPool>;
using DBConnectionPtr = std::shared_ptr<class CDDDBConnection>;
using DBProcedurePtr = std::shared_ptr<class CDDDBProcedure>;


//:: Using UniquePtr


//:: Template
template <typename T>
concept DerivedFromServerDBObject = std::is_base_of<CDDServerDBObject, T>::value;
