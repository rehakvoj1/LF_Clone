#pragma once

class I_Listener;

// =================================================================================
class Event
{
public:
    virtual ~Event();
protected:
};



// =================================================================================
class EventCallbackBase
{
public:
    void Exec( Event& e, I_Listener* listener ) { call( e, listener ); }

private:
    virtual void call( Event&, I_Listener* ) = 0;
};



// =================================================================================
template <class EventType, class SubscriberType>
class EventCallback : public EventCallbackBase
{
public:
                    EventCallback( SubscriberType& sub, void ( SubscriberType::* fn )( EventType ) );
    
    virtual void    call( Event& e, I_Listener* listener );

private:
    void ( SubscriberType::* m_callback )( EventType );
};

#include "Event.inl"