#pragma once

#include "I_Publisher.h"

class I_SystemEventHandler : public I_Publisher
{
public:
	static I_SystemEventHandler* Create();
	virtual void PollEvents() = 0;
};