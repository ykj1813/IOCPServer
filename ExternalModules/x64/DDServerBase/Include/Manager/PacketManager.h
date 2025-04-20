#pragma once

#include "Base/DDBaseSingleton.h"
#include "Header/DDServerBaseMacro.h"


class API_DDSERVERBASE CPacketManger : public TDDBaseSingleton<CPacketManger>
{
protected:
	virtual void Initialize() override;
	virtual void Release() override;


};
