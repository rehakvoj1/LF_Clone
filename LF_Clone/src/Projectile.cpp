#include "Projectile.h"
#include "C_Engine.h"
#include "I_WindowsManager.h"
#include "Renderer2D.h"
#include "EntityManager.h"
#include "CollisionSystem.h"

#include <iostream>

// =================================================================================
Projectile::Projectile( std::string id, float speed, ActorDirection dir, sf::Sprite sprite ) : 
	Actor( id ),
	m_speed( speed ),
	m_dir( dir ),
	m_sprite( sprite ),
	m_durationInSecs( PROJECTILE_DURATION_IN_SECS )

{
}

Projectile::~Projectile()
{
	ProjectileDestroyedEvent projectileDestroyed( *this );
	auto projectileDestroyedCallbacks = m_callbacks.equal_range( typeid( ProjectileDestroyedEvent ) );
	for ( auto it = projectileDestroyedCallbacks.first; it != projectileDestroyedCallbacks.second; ++it )
	{
		it->second.second->Exec( projectileDestroyed, it->second.first );
	}


	C_Engine::GetCollisionSystem()->UnregisterCollider( this );
}

// =================================================================================
void Projectile::OnUpdate( float dt )
{
	if ( m_timer.getElapsedTime().asSeconds() >= m_durationInSecs )
	{
		C_Engine::GetEntityManager()->RemoveObject( GetID() );
	}

	float deltaMoveX = m_speed * dt * m_dir;
	m_pos.x += deltaMoveX;
	m_sprite.setPosition( m_pos.x, m_pos.y );

	// Update BBox
	GetAABB2D()->t_hi = { GetAABB2D()->t_hi.x + deltaMoveX, GetAABB2D()->t_hi.y  };
	GetAABB2D()->t_lo = { GetAABB2D()->t_lo.x + deltaMoveX, GetAABB2D()->t_lo.y  };

	C_Engine::GetRenderer()->RegisterForDraw( this, Renderer2D::RenderLayer::DYNAMIC_OBJECTS );
}

// =================================================================================
void Projectile::OnRender()
{
	C_Engine::GetWindowsManager()->GetActiveWindow()->Draw( this );
}


// =================================================================================
void Projectile::OnCreate()
{
	m_timer.restart();

	sf::Sprite& sprite = static_cast<sf::Sprite&>( *GetDrawable() );
	AABB2D* aabb = GetAABB2D();
	sf::Vector2f spriteTopLeft = sprite.getGlobalBounds().getPosition();
	aabb->t_lo = { spriteTopLeft.x, spriteTopLeft.y };
	aabb->t_hi = { spriteTopLeft.x + sprite.getGlobalBounds().width, spriteTopLeft.y + sprite.getGlobalBounds().width };
}


// =================================================================================
sf::Drawable* Projectile::GetDrawable()
{
	return &m_sprite;
}

// =================================================================================
ImVec2 Projectile::GetPivot()
{
	const auto& sfmlBBox = m_sprite.getGlobalBounds();
	ImVec2 topLeft = sfmlBBox.getPosition();
	ImVec2 pivot = { topLeft.x + ( sfmlBBox.width ) / 2, topLeft.y + sfmlBBox.height };
	return pivot;
}


// =================================================================================
void Projectile::SetPosition( ImVec2 newPos )
{
	m_pos = newPos;
	sf::Sprite& sprite = static_cast<sf::Sprite&>( *GetDrawable() );
	sprite.setPosition( m_pos );
	AABB2D* aabb = GetAABB2D();
	sf::Vector2f spriteTopLeft = sprite.getGlobalBounds().getPosition();
	aabb->t_lo = { spriteTopLeft.x, spriteTopLeft.y };
	aabb->t_hi = { spriteTopLeft.x + sprite.getGlobalBounds().width, spriteTopLeft.y + sprite.getGlobalBounds().width };

}
