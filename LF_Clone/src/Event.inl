#include "Event.h"

#pragma once
template <class EventType, class SubscriberType>
EventCallback<EventType, SubscriberType>::EventCallback( SubscriberType& sub, void ( SubscriberType::* fn )( EventType ) ) : m_callback( fn )
{
}

template <typename EventType, typename SubscriberType>
void EventCallback<EventType, SubscriberType>::call( Event& e, I_Listener* listener )
{
    EventType& castedEvent = static_cast<EventType&>( e );
    ( listener.*m_callback )( castedEvent );
}