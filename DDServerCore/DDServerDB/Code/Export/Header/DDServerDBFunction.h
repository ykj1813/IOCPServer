#pragma once

#include "Header/DDServerDBType.h"


template<DerivedFromServerDBObject TDBObject, typename... Args>
static std::shared_ptr<TDBObject> Make_SharedPtr_DBObject(Args&&... args)
{
	TDBObject* NewDBObject = new TDBObject(std::forward<Args>(args)...);
	NewDBObject->Initialize();

	return std::shared_ptr<TDBObject>(NewDBObject, CDDServerDBObjectDeleter());
}

template<DerivedFromServerDBObject TDBObject>
static std::shared_ptr<TDBObject> Make_SharedPtr_DBObject(TDBObject* DBrObject)
{
	TDBObject* NewDBObject = DBrObject;
	NewDBObject->Initialize();

	return std::shared_ptr<TDBObject>(NewDBObject, CDDServerDBObjectDeleter());
}


