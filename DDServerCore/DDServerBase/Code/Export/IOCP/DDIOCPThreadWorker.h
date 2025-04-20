#pragma once

#include "Base/DDServerBaseObject.h"
#include "Interface/IDDThreadEvent.h"

#include <thread>


class API_DDSERVERBASE_CLASS CDDIOCPThreadWorker : public CDDServerBaseObject, public IDDThreadEvent
{
public:
	CDDIOCPThreadWorker() = default;
	virtual ~CDDIOCPThreadWorker() = default;

public:
	virtual void Initialize() override;
	virtual void Release() override;

	void         StartWork(struct FIOCPWorkInfo* WorkInfo);

private:
	void         ThreadWorker(struct FIOCPWorkInfo* WorkInfo);

private:
	std::thread  Thread;
	FIOCPWorkInfo WorkInfo;
};
