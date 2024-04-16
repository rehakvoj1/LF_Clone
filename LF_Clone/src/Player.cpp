#include "Player.h"
#include "C_Engine.h"
#include "I_WindowsManager.h"
#include "TextureManager.h"
#include "Renderer2D.h"
#include "GameResources.h"
#include "I_SystemEventHandler.h"
#include "EntityManager.h"
#include "Projectile.h"
#include "CollisionSystem.h"
#include "FireballProjectile.h"
#include "Actor.h"


#include <iostream>

// =================================================================================
Player::Player( std::string id, float speed, ActorDirection dir, sf::Sprite sprLeft, sf::Sprite sprRight ) :	
	Actor( id ),
	m_speed( speed ),
	m_dir( ActorDirection::RIGHT ),
	m_sprites{ sprLeft, sprRight },
	m_state{ PlayerState::NO_MOVE },
	m_health{ 100.0f },
	m_isSpellReady{ true }
{
}

// =================================================================================
void Player::OnUpdate( float dt )
{
	// update health
	if ( m_health <= 0.0f )
	{
		m_health = 100.0f;
		std::cout << "PLAYER'S CURRENT HEALTH: " << m_health << std::endl;
	}

	// update position
	float deltaMoveX = m_speed * m_dir * IsMovingLeft() * dt + m_speed * m_dir * IsMovingRight() * dt;
	float deltaMoveY = m_speed * IsMovingUp() * dt * -1.0f + m_speed * IsMovingDown() * dt;

	m_pos.x = m_pos.x + deltaMoveX;
	m_pos.y = m_pos.y + deltaMoveY;
	
	// update position of sprite
	static_cast<sf::Sprite&>( *GetDrawable() ).setPosition( m_pos.x, m_pos.y );
	
	//update position of BBox
	GetAABB2D()->t_hi = { GetAABB2D()->t_hi.x + deltaMoveX, GetAABB2D()->t_hi.y + deltaMoveY };
	GetAABB2D()->t_lo = { GetAABB2D()->t_lo.x + deltaMoveX, GetAABB2D()->t_lo.y + deltaMoveY };

	//std::cout << "t_lo: " << "[ " << GetAABB2D()->t_lo.x << ", " << GetAABB2D()->t_lo.y << " ]" << std::endl;
	//std::cout << "t_hi: " << "[ " << GetAABB2D()->t_hi.x << ", " << GetAABB2D()->t_hi.y << " ]" << std::endl;

	C_Engine::GetRenderer()->RegisterForDraw( this, Renderer2D::RenderLayer::DYNAMIC_OBJECTS );
}

// =================================================================================
void Player::OnRender()
{
	C_Engine::GetWindowsManager()->GetActiveWindow()->Draw( this );
}

// =================================================================================
void Player::OnCreate()
{
	Observe<KeyPressedEvent>( C_Engine::GetSystemEventHandler(), &Player::OnKeyPressed);
	Observe<KeyReleasedEvent>( C_Engine::GetSystemEventHandler(), &Player::OnKeyReleased );
	Observe<OverlapEvent>( C_Engine::GetCollisionSystem(), &Player::OnOverlap );
	C_Engine::GetCollisionSystem()->RegisterCollider( this, 
													  CollisionSystem::CollisionFilter::Character, 
													  static_cast<CollisionSystem::CollisionFilter>( CollisionSystem::CollisionFilter::Projectile |
																									 CollisionSystem::CollisionFilter::Character )
													);

	sf::Sprite sprite = static_cast<sf::Sprite&>( *GetDrawable() );
	AABB2D* aabb = GetAABB2D();
	sf::Vector2f spriteTopLeft = sprite.getGlobalBounds().getPosition();
	aabb->t_lo = { spriteTopLeft.x, spriteTopLeft.y};
	aabb->t_hi = { spriteTopLeft.x + sprite.getGlobalBounds().width, spriteTopLeft.y + sprite.getGlobalBounds().width };
}

// =================================================================================
ImVec2 Player::GetPivot()
{
	const auto& sfmlBBox = static_cast<sf::Sprite&>( *GetDrawable() ).getGlobalBounds();
	ImVec2 topLeft = sfmlBBox.getPosition();
	ImVec2 pivot = { topLeft.x + ( sfmlBBox.width ) / 2, topLeft.y + sfmlBBox.height };
	return pivot;
}


// =================================================================================
sf::Drawable* Player::GetDrawable()
{
	int idx = ( m_dir + 1 ) / 2;
	return &(m_sprites[idx]);
}



// =================================================================================
Actor* Player::CreateSorcerer( std::string id )
{
	sf::Texture& sorcererRight = C_Engine::GetTextureManager()->GetTexture( g_texFilepaths.at( ecTexture::SORCERER ) );
	sf::Texture& sorcererLeft = C_Engine::GetTextureManager()->GetTexture( g_texFilepaths.at( ecTexture::SORCERER_MIRROR ) );
	return new Player	(	id,
							PLAYER_SPEED,
							ActorDirection::RIGHT,
							sf::Sprite( sorcererLeft, sf::IntRect( { 720,0 }, { 80,80 } ) ),
							sf::Sprite( sorcererRight, sf::IntRect( { 0,0 }, { 80,80 } ) )
						);
}

void Player::TakeDamage( float damage )
{
	m_health -= damage;

	HitEvent hit( damage, *this );
	auto hitCallbacks = m_callbacks.equal_range( typeid( HitEvent ) );
	for ( auto it = hitCallbacks.first; it != hitCallbacks.second; ++it )
	{
		it->second.second->Exec( hit, it->second.first );
	}

	std::cout << "PLAYER'S CURRENT HEALTH: " << m_health << std::endl;
}


// =================================================================================
bool Player::IsMovingUp() const
{
	return (m_state & PlayerState::MOVE_UP);
}


// =================================================================================
bool Player::IsMovingDown() const
{
	return ( m_state & PlayerState::MOVE_DOWN );
}


// =================================================================================
bool Player::IsMovingLeft() const
{
	return ( m_state & PlayerState::MOVE_LEFT );
}


// =================================================================================
bool Player::IsMovingRight() const
{
	return ( m_state & PlayerState::MOVE_RIGHT );
}


// =================================================================================
void Player::OnKeyPressed( KeyPressedEvent& e )
{
	switch ( e.GetKey() )
	{
		case sf::Keyboard::A:
		case sf::Keyboard::Left:
			m_state = static_cast<PlayerState>(m_state | PlayerState::MOVE_LEFT);
			m_state = static_cast<PlayerState>( m_state & ~PlayerState::MOVE_RIGHT );
			m_dir = ActorDirection::LEFT;
			break;
		case sf::Keyboard::D:
		case sf::Keyboard::Right:
			m_state = static_cast<PlayerState>( m_state | PlayerState::MOVE_RIGHT );
			m_state = static_cast<PlayerState>( m_state & ~PlayerState::MOVE_LEFT );
			m_dir = ActorDirection::RIGHT;
			break;
		case sf::Keyboard::W:
		case sf::Keyboard::Up:
			m_state = static_cast<PlayerState>( m_state | PlayerState::MOVE_UP );
			m_state = static_cast<PlayerState>( m_state & ~PlayerState::MOVE_DOWN );
			break;
		case sf::Keyboard::S:
		case sf::Keyboard::Down:
			m_state = static_cast<PlayerState>( m_state | PlayerState::MOVE_DOWN );
			m_state = static_cast<PlayerState>( m_state & ~PlayerState::MOVE_UP );
			break;

		case sf::Keyboard::Space:
			if ( m_isSpellReady )
			{
				Projectile* proj = nullptr;
				if ( m_dir == ActorDirection::LEFT )
				{
					proj = static_cast<Projectile*>( C_Engine::GetEntityManager()->AddObject( "frostboltLeft", "frostbolt", true ) );
					proj->SetPosition( { m_pos.x - STARTING_FROSTBOLT_OFFSET_X, m_pos.y - STARTING_FROSTBOLT_OFFSET_Y } );
				}
				else
				{
					proj = static_cast<Projectile*>( C_Engine::GetEntityManager()->AddObject( "frostboltRight", "frostbolt", true ) );
					proj->SetPosition( { m_pos.x + STARTING_FROSTBOLT_OFFSET_X, m_pos.y + STARTING_FROSTBOLT_OFFSET_Y } );
				}
				m_isSpellReady = false;
				Observe<ProjectileDestroyedEvent>( proj, &Player::OnProjectileDestroyed );
			}
			break;
	}
}


// =================================================================================
void Player::OnKeyReleased( KeyReleasedEvent& e )
{
	switch ( e.GetKey() )
	{
		case sf::Keyboard::A:
		case sf::Keyboard::Left:
			m_state = static_cast<PlayerState>( m_state & ~PlayerState::MOVE_LEFT );
			break;
		case sf::Keyboard::D:
		case sf::Keyboard::Right:
			m_state = static_cast<PlayerState>( m_state & ~PlayerState::MOVE_RIGHT );
			break;
		case sf::Keyboard::W:
		case sf::Keyboard::Up:
			m_state = static_cast<PlayerState>( m_state & ~PlayerState::MOVE_UP );
			break;
		case sf::Keyboard::S:
		case sf::Keyboard::Down:
			m_state = static_cast<PlayerState>( m_state & ~PlayerState::MOVE_DOWN );
			break;
	}
}

void Player::OnOverlap( OverlapEvent& e )
{
	if ( e.GetTarget().GetID() == "fireball" )
	{
		FireballProjectile& fireball = static_cast<FireballProjectile&>( e.GetTarget() );
		TakeDamage( fireball.GetDamage() );
	}
}

void Player::OnProjectileDestroyed( ProjectileDestroyedEvent& e )
{
	if ( e.GetProjectile().GetID() == "frostbolt" )
	{
		m_isSpellReady = true;
	}
	
}
