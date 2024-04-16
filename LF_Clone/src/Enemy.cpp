#include "Enemy.h"
#include "C_Engine.h"
#include "I_WindowsManager.h"
#include "TextureManager.h"
#include "Renderer2D.h"
#include "GameResources.h"
#include "CollisionSystem.h"
#include "FireballProjectile.h"
#include "EntityManager.h"


// =================================================================================
Enemy::Enemy( std::string id, float speed, ActorDirection dir, sf::Sprite sprLeft, sf::Sprite sprRight ) :
	Actor( id ),
	m_speed( speed ),
	m_dir( ActorDirection::RIGHT ),
	m_sprites{ sprLeft, sprRight },
	m_isSpellReady{ true }
{
}


// =================================================================================
void Enemy::OnUpdate( float dt )
{

	sf::Sprite& sprite = static_cast<sf::Sprite&>( *GetDrawable() );
	
	if ( m_isSpellReady )
	{
		Projectile* proj = nullptr;
		if ( m_dir == ActorDirection::LEFT )
		{
			proj = static_cast<Projectile*>( C_Engine::GetEntityManager()->AddObject( "fireballLeft", "fireball", true ) );
			proj->SetPosition( { m_pos.x - STARTING_FIREBALL_OFFSET_X, m_pos.y - STARTING_FIREBALL_OFFSET_Y } );
		}
		else
		{
			proj = static_cast<Projectile*>( C_Engine::GetEntityManager()->AddObject( "fireballRight", "fireball", true ) );
			proj->SetPosition( { m_pos.x + STARTING_FIREBALL_OFFSET_X, m_pos.y + STARTING_FIREBALL_OFFSET_Y } );
		}
		m_isSpellReady = false;
		Observe<ProjectileDestroyedEvent>( proj, &Enemy::OnProjectileDestroyed );
	}



	C_Engine::GetRenderer()->RegisterForDraw( this, Renderer2D::RenderLayer::DYNAMIC_OBJECTS );
}


// =================================================================================
void Enemy::OnRender()
{
	C_Engine::GetWindowsManager()->GetActiveWindow()->Draw( this );
}


// =================================================================================
void Enemy::OnCreate()
{
	Observe<OverlapEvent>( C_Engine::GetCollisionSystem(), &Enemy::OnOverlap );
	C_Engine::GetCollisionSystem()->RegisterCollider( this,
													  CollisionSystem::CollisionFilter::Character,
													  static_cast<CollisionSystem::CollisionFilter>(CollisionSystem::CollisionFilter::Projectile | 
																									 CollisionSystem::CollisionFilter::Character )
	);

	sf::Sprite& sprite = static_cast<sf::Sprite&>( *GetDrawable() );
	m_pos = { 10,100 };
	sprite.setPosition( m_pos );
	AABB2D* aabb = GetAABB2D();
	sf::Vector2f spriteTopLeft = sprite.getGlobalBounds().getPosition();
	aabb->t_lo = { spriteTopLeft.x, spriteTopLeft.y };
	aabb->t_hi = { spriteTopLeft.x + sprite.getGlobalBounds().width, spriteTopLeft.y + sprite.getGlobalBounds().width };
}

void Enemy::OnOverlap( OverlapEvent& e )
{
}



// =================================================================================
sf::Drawable* Enemy::GetDrawable()
{
	int idx = ( m_dir + 1 ) / 2;
	return &(m_sprites[idx]);
}

// =================================================================================
ImVec2 Enemy::GetPivot()
{
	const auto& sfmlBBox = static_cast<sf::Sprite&>( *GetDrawable() ).getGlobalBounds();
	ImVec2 topLeft = sfmlBBox.getPosition();
	ImVec2 pivot = { topLeft.x + ( sfmlBBox.width ) / 2, topLeft.y + sfmlBBox.height };
	return pivot;
}


// =================================================================================
Actor* Enemy::Create( std::string id )
{
	sf::Texture& enemyRight = C_Engine::GetTextureManager()->GetTexture( g_texFilepaths.at( ecTexture::ENEMY ) );
	sf::Texture& enemyLeft = C_Engine::GetTextureManager()->GetTexture( g_texFilepaths.at( ecTexture::ENEMY_MIRROR ) );
	return new Enemy( id,
					   ENEMY_SPEED,
					   ActorDirection::RIGHT,
					   sf::Sprite( enemyLeft, sf::IntRect( { 720,0 }, { 80,80 } ) ),
					   sf::Sprite( enemyRight, sf::IntRect( { 0,0 }, { 80,80 } ) )
	);
}



void Enemy::OnProjectileDestroyed( ProjectileDestroyedEvent& e )
{
	if ( e.GetProjectile().GetID() == "fireball" )
	{
		m_isSpellReady = true;
	}
}