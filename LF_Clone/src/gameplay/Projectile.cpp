#include "Projectile.h"

//=======================================================================================================
Projectile::Projectile() :
	m_currSprite{SpriteOrientation::Invalid},
	m_pos{0.0f,0.0f},
	m_speed{0.0f},
	m_duration{0.0f},
	m_collided{ false },
	m_isCasted{ false },
	m_cooldown{0.0f}
{
	m_projectileSprites.emplace( SpriteOrientation::Invalid, sf::Sprite() );
	m_projectileSprites[m_currSprite].setColor( sf::Color::Transparent );
}

//=======================================================================================================
Projectile::Projectile( sf::Sprite& spriteDefault ) :
	m_currSprite{ SpriteOrientation::Default },
	m_pos{ 0.0f,0.0f },
	m_speed{ 0.0f },
	m_duration{ 0.0f },
	m_collided{ false },
	m_isCasted{ false },
	m_cooldown{ 0.0f }
{
	m_projectileSprites.emplace( SpriteOrientation::Default, spriteDefault );
	m_projectileSprites[m_currSprite].setPosition( m_pos );
}

//=======================================================================================================
Projectile::Projectile( sf::Sprite& spriteDefault, sf::Sprite& spriteMirror ) :
	m_currSprite{ SpriteOrientation::Default },
	m_pos{ 0.0f,0.0f },
	m_speed{ 0.0f },
	m_duration{ 0.0f },
	m_collided{ false },
	m_isCasted{ false },
	m_cooldown{ 0.0f }
{
	m_projectileSprites.emplace( SpriteOrientation::Default, spriteDefault );
	m_projectileSprites.emplace( SpriteOrientation::Mirror, spriteMirror );
	m_projectileSprites[m_currSprite].setPosition( m_pos );
}

//=======================================================================================================
void Projectile::Cast(ImVec2 startLoc, SpriteOrientation casterDir)
{
	if( !m_isCasted )
	{
		m_pos = startLoc;
		m_currSprite = casterDir;
		m_projectileSprites[m_currSprite].setPosition( m_pos );
		m_projectileSprites[m_currSprite].setColor( sf::Color::White );
		m_isCasted = true;
		ResetTimer();
	}
}

//=======================================================================================================
void Projectile::ResetTimer()
{
	m_timer.restart();
}

//=======================================================================================================
void Projectile::OnUpdate( float dt )
{
	if ( m_isCasted )
	{
		if ( m_timer.getElapsedTime().asSeconds() < m_duration && !m_collided )
		{
			m_pos.x += m_speed * dt * GetDirection();
			m_projectileSprites[m_currSprite].setPosition( m_pos );
		}
		else
		{
			m_isCasted = false;
			m_collided = false;
			m_projectileSprites[m_currSprite].setColor( sf::Color::Transparent );
			ResetTimer();
		}
	}
}

//=======================================================================================================
sf::Time Projectile::GetElapsedTime()
{
	return m_timer.getElapsedTime();
}

//=======================================================================================================
ImVec2 Projectile::GetPosition()
{
	return m_pos;
}

//=======================================================================================================
int Projectile::GetDirection()
{
	return m_currSprite == SpriteOrientation::Default ? 1 : -1;
}

//=======================================================================================================
float Projectile::GetCooldown()
{
	return m_cooldown;
}

//=======================================================================================================
sf::Sprite& Projectile::GetCurrentSprite()
{
	return m_projectileSprites[m_currSprite];
}

//=======================================================================================================
bool Projectile::IsCasted()
{
	return m_isCasted;
}

//=======================================================================================================
void Projectile::AddSprite( sf::Sprite sprite, SpriteOrientation spriteOrientation )
{
	m_projectileSprites.emplace( spriteOrientation, sprite );
}

//=======================================================================================================
void Projectile::SetSprite( SpriteOrientation spriteOrientation )
{
	m_currSprite = spriteOrientation;
}

//=======================================================================================================
void Projectile::SetSpeed( float speed )
{
	m_speed = speed;
}
//=======================================================================================================
void Projectile::SetDuration( float duration )
{
	m_duration = duration;
}

//=======================================================================================================
void Projectile::SetCooldown( float cooldown )
{
	m_cooldown = cooldown;
}

//=======================================================================================================
void Projectile::SetPosition( ImVec2 pos )
{
	m_pos = pos;
}

//=======================================================================================================
void Projectile::SetCollision( bool collided )
{
	m_collided = collided;
}
