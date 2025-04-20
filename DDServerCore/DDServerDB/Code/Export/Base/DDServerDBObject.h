#pragma once

#include "Header/DDServerDBMacro.h"
#include <shared_mutex>


class API_DDSERVERDB_CLASS CDDServerDBObject
{
public:
	CDDServerDBObject() = default;
	virtual ~CDDServerDBObject() = default;

public:
	virtual void        Initialize() PURE;
	virtual void        Release() PURE;

protected:
	std::shared_mutex   Mutex;

};

class API_DDSERVERDB_CLASS CDDServerDBObjectDeleter
{
public:
	void operator()(CDDServerDBObject* ptr)
	{
		ptr->Release();
		delete ptr;
	}
};
