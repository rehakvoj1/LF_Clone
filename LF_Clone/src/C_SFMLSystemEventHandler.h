#pragma once
#include "I_SystemEventHandler.h"
class C_SFMLSystemEventHandler : public I_SystemEventHandler
{
public:
	virtual void PollEvents() override;
};

