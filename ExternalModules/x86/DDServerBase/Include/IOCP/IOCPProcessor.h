#pragma once

#include "Base/DDServerBaseObject.h"
#include <list>
#include <mutex>
#include "Header/DDServerBaseMacro.h"


class API_DDSERVERBASE_CLASS CIOCPProcessor : public CDDServerBaseObject
{
public:
	CIOCPProcessor();
	virtual ~CIOCPProcessor();

public:
	virtual void Initialize();
	virtual void Release();

protected:
	virtual class CDDIOCPObject* CreateIOCPObject()PURE;

protected:
	virtual void TryConnect();

private:
	class CDDIOCPObject* Private_PopReserveIOCPObject();
	size_t Private_PushReserveIOCPObject(class CDDIOCPObject* _pReserveObject);

protected:
	std::mutex m_InstanceMutex;

private:
	std::list<class CDDIOCPObject*> m_ConnectedIOCPObjects;
	std::list<class CDDIOCPObject*> m_ReserveIOCPObjects;

};
