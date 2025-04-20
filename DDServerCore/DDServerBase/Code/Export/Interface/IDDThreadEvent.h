#pragma once

#include <queue>
#include <shared_mutex>
#include "Header/DDServerBaseMacro.h"
#include "Header/DDServerBaseStruct.h"



class API_DDSERVERBASE_INTERFACE IDDThreadEvent
{
public:
	IDDThreadEvent() = default;
	virtual ~IDDThreadEvent() = default;

protected:
	void                     PushThreadEvent(FThreadEvent _ThreadEvent);
	FThreadEvent             PopThreadEvent();
	void                     ClearThreadEvent();
	size_t                   GetEventSize();

private:
	std::queue<FThreadEvent> m_Events;
	std::shared_mutex        m_ThreadEventMutex;
};
