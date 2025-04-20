#pragma once

#include "Header/DDServerBaseMacro.h"
#include <shared_mutex>


class API_DDSERVERBASE_CLASS CDDServerBaseObject
{
public:
	CDDServerBaseObject() = default;
	virtual ~CDDServerBaseObject() = default;

public:
	virtual void        Initialize() PURE;
	virtual void        Release() PURE;

protected:
	std::shared_mutex   Mutex;

};

class API_DDSERVERBASE_CLASS CDDServerBaseObjectDeleter
{
public:
	void operator()(CDDServerBaseObject* ptr)
	{
		ptr->Release();
		delete ptr;
	}
};
