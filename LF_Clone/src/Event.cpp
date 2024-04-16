#include "Event.h"
#include "GameObject.h"
#include "Actor.h"

// =================================================================================
Event::~Event()
{
}


// =================================================================================
// ============================= WINDOW RESIZED ====================================
// =================================================================================
WindowResizedEvent::WindowResizedEvent( unsigned int width, unsigned int height ) : m_width(width),
																					m_height(height)
{
}

// =================================================================================
unsigned int WindowResizedEvent::GetWidth() const
{
	return m_width;
}

// =================================================================================
unsigned int WindowResizedEvent::GetHeight() const
{
	return m_height;
}

// =================================================================================
// =================================================================================
//  =================================================================================




// =================================================================================
// ================================ KEY PRESSED ====================================
// =================================================================================
KeyPressedEvent::KeyPressedEvent( KeyModifier keyMod, sf::Keyboard::Key key ) : m_keyMod(keyMod),
																				m_key(key)
{
}


// =================================================================================
sf::Keyboard::Key KeyPressedEvent::GetKey()
{
	return m_key;
}


// =================================================================================
// ================================ COLLISION ======================================
// =================================================================================
OverlapEvent::OverlapEvent( GameObject& tar ) : m_target( tar )
{
}


// =================================================================================
GameObject& OverlapEvent::GetTarget()
{
	return m_target;
}


// =================================================================================
// ================================ KEY RELEASED ===================================
// =================================================================================
KeyReleasedEvent::KeyReleasedEvent( sf::Keyboard::Key key ) : m_key{ key }
{
}

sf::Keyboard::Key KeyReleasedEvent::GetKey()
{
	return m_key;
}



// =================================================================================
// ================================ KEY RELEASED ===================================
// =================================================================================
ProjectileDestroyedEvent::ProjectileDestroyedEvent( Projectile& projectile ) : m_projectile{ projectile }
{
}

Projectile& ProjectileDestroyedEvent::GetProjectile()
{
	return m_projectile;
}

HitEvent::HitEvent( float damage, Actor& target ) : m_damage(damage), m_target(target)
{
}

Actor& HitEvent::GetTarget()
{
	return m_target;
}

float HitEvent::GetDamage()
{
	return m_damage;
}
