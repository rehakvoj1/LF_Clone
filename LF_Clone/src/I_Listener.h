#pragma once

#include <vector>
#include <string>

#include "Event.h"

class I_Publisher;

class I_Listener
{
public:

			I_Listener();
	virtual ~I_Listener();

	template <typename EventType, typename SubscriberType>
	void Observe( I_Publisher* pub, void ( SubscriberType::* fn )( EventType& ) );



protected:
	std::vector<I_Publisher*>	m_publishers;
	
private:
};

#include "I_Listener.inl"
