#include "I_Publisher.h"

#pragma once
#include "I_Listener.h"
#include "Event.h"

// =================================================================================
template<class EventType, class SubscriberType>
inline void I_Publisher::RegisterListener( I_Listener* listener, void( SubscriberType::* fn )( EventType& ) )
{
	m_eventsPerListener.emplace( listener, typeid( EventType ) );
	EventCallbackBase* cb = new EventCallback( fn );
	std::pair<I_Listener*, EventCallbackBase*> pair = { listener, cb };
	m_callbacks.emplace( typeid( EventType ), pair );
}