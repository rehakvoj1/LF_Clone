#include "I_Publisher.h"


// =================================================================================
I_Publisher::I_Publisher()
{
}


// =================================================================================
I_Publisher::~I_Publisher()
{
}


// =================================================================================
void I_Publisher::UnregisterListener( I_Listener* listener )
{
	auto eventsOfListenerRange = m_eventsPerListener.equal_range( listener );
	for ( auto it = eventsOfListenerRange.first; it != eventsOfListenerRange.second; ++it )
	{
		auto callbacksOfEventRange = m_callbacks.equal_range( it->second );
		for ( auto it2 = callbacksOfEventRange.first; it2 != callbacksOfEventRange.second; ++it2 )
		{
			if ( it2->second.first == listener )
			{
				delete it2->second.second;
				m_callbacks.erase( it2 );	//	Deletes callbacks of listener
			}
		}
	}
	m_eventsPerListener.erase( listener );	//	Deletes list of registered events of listener
}
