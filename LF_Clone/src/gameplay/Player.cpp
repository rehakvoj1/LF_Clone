#include "Player.h"

//=======================================================================================================
Player::Player( sf::Sprite& spriteDefault, sf::Sprite& spriteMirror ) :
    m_currSprite( SpriteOrientation::Default ),
    m_pos{ 0.0f,0.0f },
    m_health{ 100.f },
    m_speed{ 200.f }
{
    m_playerSprites.emplace( SpriteOrientation::Default, spriteDefault );
    m_playerSprites.emplace( SpriteOrientation::Mirror, spriteMirror );
    m_playerSprites[m_currSprite].setPosition( m_pos );

}

//=======================================================================================================
void Player::OnUpdate( float dt )
{
    if ( m_health < 0 )
    {
        m_health = 100;
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) ||
         sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
    {
        m_pos.y -= m_speed * dt;
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ||
         sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
    {
        m_pos.y += m_speed * dt;
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ||
         sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
    {
        m_currSprite = SpriteOrientation::Mirror;
        m_pos.x -= m_speed * dt;
    }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ||
         sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
    {
        m_currSprite = SpriteOrientation::Default;
        m_pos.x += m_speed * dt;
    }

    m_playerSprites[m_currSprite].setPosition( m_pos );


    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
    {
        m_frostbolt.Cast( ImVec2( m_pos.x + 25 * GetDirection(), m_pos.y - 6 ),m_currSprite );
    }


    m_frostbolt.OnUpdate( dt ); /* Should be independent of Player -> now updating of player updates projectile */
}

//=======================================================================================================
void Player::OnRender( sf::RenderWindow& window )
{
    window.draw( GetCurrentSprite() );
    window.draw( m_frostbolt.GetCurrentSprite() );
}

//=======================================================================================================
sf::Sprite& Player::GetCurrentSprite()
{
    return m_playerSprites[m_currSprite];
}

//=======================================================================================================
int Player::GetDirection()
{
    return m_currSprite == SpriteOrientation::Default ? 1 : -1;
}

//=======================================================================================================
float Player::GetHealth()
{
    return m_health;
}

//=======================================================================================================
Projectile& Player::GetProjectile()
{
    return m_frostbolt;
}

//=======================================================================================================
void Player::SetHealth( float val )
{
    m_health = val;
}

//=======================================================================================================
void Player::SetProjectile( SpriteOrientation so, sf::Sprite sprite, float speed, float duration, float cooldown )
{
    m_frostbolt.AddSprite( sprite, so );
    m_frostbolt.SetSpeed( speed );
    m_frostbolt.SetDuration( duration );
    m_frostbolt.SetCooldown( cooldown );
}

//=======================================================================================================
void Player::TakeDamage( float damage )
{
    m_health -= damage;
}
