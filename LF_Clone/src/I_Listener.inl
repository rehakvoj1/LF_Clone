#include "I_Listener.h"
#pragma once
#include "I_Publisher.h"



// =================================================================================
template<typename EventType, typename SubscriberType>
inline void I_Listener::Observe( I_Publisher* pub, void( SubscriberType::* fn )( EventType& ) )
{
	pub->RegisterListener<EventType>( this, fn );
	m_publishers.push_back( pub );
}