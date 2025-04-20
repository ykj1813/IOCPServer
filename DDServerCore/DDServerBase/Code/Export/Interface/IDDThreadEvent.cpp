#include "pch.h"
#include "Interface/IDDThreadEvent.h"


void IDDThreadEvent::PushThreadEvent(FThreadEvent _ThreadEvent)
{
	LOCK_GUARD(m_ThreadEventMutex);

	m_Events.push(_ThreadEvent);
}

FThreadEvent IDDThreadEvent::PopThreadEvent()
{
	LOCK_GUARD(m_ThreadEventMutex);

	if (0 == m_Events.size())
	{
		return FThreadEvent();
	}

	FThreadEvent Pop = m_Events.front();
	m_Events.pop();
	return Pop;
}

void IDDThreadEvent::ClearThreadEvent()
{
	LOCK_GUARD(m_ThreadEventMutex);

	std::queue<FThreadEvent> empty;
	std::swap(m_Events, empty);
}

size_t IDDThreadEvent::GetEventSize()
{
	LOCK_SHARED(m_ThreadEventMutex);

	return m_Events.size();
}
