#pragma once

#include <string>
#include <typeindex>
#include <unordered_map>
#include <set>

#include "Event.h"


class I_Listener;

class I_Publisher
{
public:
            I_Publisher();
    virtual ~I_Publisher();

    template <class EventType, class SubscriberType>
    void RegisterListener( I_Listener* listener, void ( SubscriberType::* fn )( EventType& ) );
	void UnregisterListener( I_Listener* listener );

protected:
    std::unordered_multimap< std::type_index, std::pair<I_Listener*,EventCallbackBase*> > m_callbacks; // idx: event; val: listener+callback
    std::unordered_multimap< I_Listener*, std::type_index > m_eventsPerListener;

private:
};

#include "I_Publisher.inl"
