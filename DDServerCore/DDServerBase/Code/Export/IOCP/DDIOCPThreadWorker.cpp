#include "pch.h"
#include "DDIOCPThreadWorker.h"
#include <thread>

#include "Header/DDServerBaseStruct.h"
#include "IOCP/DDIOCPObject.h"


// CDDIOCPThreadWorker::CDDIOCPThreadWorker()
// {
// 
// }
// 
// CDDIOCPThreadWorker::~CDDIOCPThreadWorker()
// {
// 
// }

void CDDIOCPThreadWorker::Initialize()
{
	LOCK_GUARD(Mutex);

}

void CDDIOCPThreadWorker::Release()
{
	LOCK_GUARD(Mutex);

}

void CDDIOCPThreadWorker::StartWork(FIOCPWorkInfo* WorkInfo)
{
	LOCK_GUARD(Mutex);

	this->WorkInfo = *WorkInfo;

	Thread = std::thread(&CDDIOCPThreadWorker::ThreadWorker, this, &this->WorkInfo);
}

void CDDIOCPThreadWorker::ThreadWorker(FIOCPWorkInfo* WorkInfo)
{
	FThreadEvent ThreadEvent;

	DWORD       bytesTransferred;
	ULONG_PTR   completionKey;
	OVERLAPPED* overlapped;

	while (true)
	{
		ThreadEvent = PopThreadEvent();
		if (EThreadEvent::Stop == ThreadEvent.Event)
		{
			break;
		}

		//:: 이벤트가 더 남아있다.
		if (EThreadEvent::Unknown != ThreadEvent.Event)
		{
			continue;
		}

		//:: IOCP
		//
		BOOL result = ::GetQueuedCompletionStatus(WorkInfo->IOCPHandle, &bytesTransferred, &completionKey, &overlapped, INFINITE);

		if (TRUE == result)
		{
			FDDOverlapped* pOverlapped = reinterpret_cast<FDDOverlapped*>(overlapped);
			pOverlapped->WorkInfo = WorkInfo;

			pOverlapped->Owner->Dispatch(pOverlapped, bytesTransferred);

			LOCK_GUARD(Mutex);
		}
		else
		{
			LOCK_GUARD(Mutex);

		}

		Sleep(0);
	}
}
