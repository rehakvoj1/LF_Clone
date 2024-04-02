#pragma once

#include <string>
#include <typeindex>
#include <unordered_map>
#include <set>

#include "Event.h"


// struct for hashing pair as key in unordered map
struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() ( const std::pair<T1, T2>& pair ) const
    {
        return std::hash<T1>()( pair.first ) ^ std::hash<T2>()( pair.second );
    }
};  


class I_Listener;

class I_Publisher
{
public:
            I_Publisher();
    virtual ~I_Publisher();

    template <class EventType, class SubscriberType>
    void RegisterListener( I_Listener* listener, void ( SubscriberType::* fn )( EventType ) );
	void UnregisterListener( I_Listener* listener );

protected:
    std::unordered_map< std::pair<std::type_index, I_Listener*>, EventCallbackBase*, pair_hash> m_callbacks; // idx: listener+event; val: callback
    std::unordered_map<std::type_index, unsigned int> m_registeredEvents;

private:
};

#include "I_Publisher.inl"
