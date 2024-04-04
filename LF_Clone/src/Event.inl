#include "Event.h"

#pragma once
// =================================================================================
template <class EventType, class SubscriberType>
EventCallback<EventType, SubscriberType>::EventCallback( void ( SubscriberType::* fn )( EventType ) ) : m_callback( fn )
{
}


// =================================================================================
template <typename EventType, typename SubscriberType>
void EventCallback<EventType, SubscriberType>::call( Event& e, I_Listener* listener )
{
    EventType& castedEvent = static_cast<EventType&>( e );
    SubscriberType* castedListener = static_cast<SubscriberType*>( listener );
    ( castedListener->*m_callback )( castedEvent );
}