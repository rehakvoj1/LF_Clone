#include "Enemy.h"

Enemy::Enemy( sf::Sprite& spriteDefault ) : 
    m_currSprite( SpriteOrientation::Default ),
    m_pos{ 80.0f, 80.0f },
    m_health{ 100.f },
    m_speed{ 200.f }
{
    m_enemySprites.emplace( SpriteOrientation::Default, spriteDefault );
    m_enemySprites[m_currSprite].setPosition( m_pos );
}

Enemy::Enemy( sf::Sprite& spriteDefault, sf::Sprite& spriteMirror ) :
    m_currSprite( SpriteOrientation::Default ),
    m_pos{ 80.0f, 80.0f },
    m_health{ 100.f },
    m_speed{ 200.f }
{
    m_enemySprites.emplace( SpriteOrientation::Default, spriteDefault );
    m_enemySprites.emplace( SpriteOrientation::Mirror, spriteMirror );
    m_enemySprites[m_currSprite].setPosition( m_pos );

}

void Enemy::OnUpdate( float dt )
{
    if ( m_fireball.GetElapsedTime().asSeconds() > m_fireball.GetCooldown() )
    {
        m_fireball.Cast( ImVec2( m_pos.x + 25 * GetDirection(), m_pos.y - 6 ), m_currSprite );
    }

    m_fireball.OnUpdate( dt ); /* Should be independent of Enemy -> now updating of enemy updates projectile */
}

void Enemy::OnRender( sf::RenderWindow& window )
{
    window.draw( GetCurrentSprite() );
    window.draw( m_fireball.GetCurrentSprite() );
}

sf::Sprite& Enemy::GetCurrentSprite()
{
    return m_enemySprites[m_currSprite];
}

int Enemy::GetDirection()
{
    return m_currSprite == SpriteOrientation::Default ? 1 : -1;
}

Projectile& Enemy::GetProjectile()
{
    return m_fireball;
}

void Enemy::SetProjectile( SpriteOrientation so, sf::Sprite sprite, float speed, float duration, float cooldown )
{
    m_fireball.AddSprite( sprite, so );
    m_fireball.SetSpeed( speed );
    m_fireball.SetDuration( duration );
    m_fireball.SetCooldown( cooldown );
}

void Enemy::TakeDamage( float damage )
{
    m_health -= damage;
}
