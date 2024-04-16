#include "I_Listener.h"
#include "I_Publisher.h"

#include <iostream>

// =================================================================================
I_Listener::I_Listener()
{
}

// =================================================================================
I_Listener::~I_Listener()
{
	for ( auto& pub : m_publishers )
	{
		pub->UnregisterListener( this );
	}
}
