#pragma once

#include <SFML/Window/Event.hpp>

class I_Listener;
class GameObject;
class Actor;

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
                    EventCallback( void ( SubscriberType::* fn )( EventType ) );
    
    virtual void    call( Event& e, I_Listener* listener );

private:
    void ( SubscriberType::* m_callback )( EventType );
};



// =================================================================================
class WindowClosedEvent : public Event
{

};



// =================================================================================
class WindowResizedEvent : public Event
{
public:
    explicit WindowResizedEvent( unsigned int width, unsigned int height );

    unsigned int GetWidth() const;
    unsigned int GetHeight() const;

private:
    unsigned int m_width;
    unsigned int m_height;
};



// =================================================================================
class KeyPressedEvent : public Event
{
public:
    enum KeyModifier
    {
        NOMOD = 0,
        CONTROL = 1,
        SHIFT = 2,
        ALT = 4
    }; 

public:
    explicit KeyPressedEvent( KeyModifier keyMod, sf::Keyboard::Key );
    sf::Keyboard::Key GetKey();

private:
    KeyModifier m_keyMod;
    sf::Keyboard::Key m_key;
};


// =================================================================================
class KeyReleasedEvent : public Event
{
public:
    explicit KeyReleasedEvent( sf::Keyboard::Key );
    sf::Keyboard::Key GetKey();

private:
    sf::Keyboard::Key m_key;
};


// =================================================================================
class OverlapEvent : public Event
{
public:
    explicit OverlapEvent( GameObject& tar );
    GameObject& GetTarget();

private:
    GameObject& m_target;
};



// =================================================================================
class Projectile;
class ProjectileDestroyedEvent : public Event
{
public:
    explicit ProjectileDestroyedEvent( Projectile& projectile );
    Projectile& GetProjectile();

private:
    Projectile& m_projectile;
};



// =================================================================================
class HitEvent : public Event
{
public:
    explicit HitEvent( float damage, Actor& target );
    
    Actor& GetTarget();
    float GetDamage();

private:
    float m_damage;
    Actor& m_target;
};

#include "Event.inl"