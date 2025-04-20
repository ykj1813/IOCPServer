#pragma once

#include "Base/DDServerBaseObject.h"
#include "Header/DDServerBaseType.h"


template<DerivedFromServerBaseObject TServerObject>
static std::shared_ptr<TServerObject> Make_SharedPtr_ServerObject(TServerObject* ServerObject = nullptr)
{
	TServerObject* NewServerObject = ServerObject;
	if (nullptr == NewServerObject)
	{
		NewServerObject = new TServerObject;
		NewServerObject->Initialize();
	}

	return std::shared_ptr<TServerObject>(NewServerObject, CDDServerBaseObjectDeleter());
}

template<typename T>
static inline bool SetSockOpt(SOCKET Socket, int32 Level, int32 OptName, T OptVal)
{
	return SOCKET_ERROR != ::setsockopt(Socket, Level, OptName, reinterpret_cast<char*>(&OptVal), sizeof(T));
}


