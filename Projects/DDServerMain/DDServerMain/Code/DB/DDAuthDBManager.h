#pragma once

#include "Base/DDBaseSingleton.h"
#include "Interface/DDDBManager.h"


class CDDAuthDBManager : public IDDDBManager, public TDDBaseSingleton<CDDAuthDBManager>
{
public:
	CDDAuthDBManager();
	virtual ~CDDAuthDBManager();

public:
	virtual void Initialize() override;
	virtual void Release() override;


};
