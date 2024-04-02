#include "I_Publisher.h"

I_Publisher::I_Publisher()
{
}

I_Publisher::~I_Publisher()
{
}

void I_Publisher::UnregisterListener( I_Listener* listener )
{
	for ( auto it = m_registeredEvents.begin(); it != m_registeredEvents.end(); ++it )
	{
		m_callbacks.erase( { it->first,listener } );
		it->second -= 1;
		
		if ( it->second <= 0 )
		{
			m_registeredEvents.erase( it );
		}
	}
}
