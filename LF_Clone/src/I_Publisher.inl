#include "I_Publisher.h"

#pragma once


template<class EventType, class SubscriberType>
inline void I_Publisher::RegisterListener( I_Listener* listener, void( SubscriberType::* fn )( EventType ) )
{
	m_callbacks.insert_or_assign( { typeid( EventType ),listener }, fn );
	m_registeredEvents[typeid( EventType )] += 1;
}