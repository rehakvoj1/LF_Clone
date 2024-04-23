#include "FireballProjectile.h"
#include "C_Engine.h"
#include "TextureManager.h"
#include "GameResources.h"
#include "CollisionSystem.h"
#include "EntityManager.h"

//===================================================================================================
FireballProjectile::FireballProjectile( std::string id, float speed, ActorDirection dir, sf::Sprite sprite ) :
	Projectile( id, speed, dir, sprite ),
	m_damage( FIREBALL_DAMAGE )
{
}

//===================================================================================================
FireballProjectile::~FireballProjectile()
{

}


//===================================================================================================
void FireballProjectile::OnCreate()
{
	Projectile::OnCreate();

	Observe<OverlapEvent>( C_Engine::GetCollisionSystem(), &FireballProjectile::OnOverlap );
	C_Engine::GetCollisionSystem()->RegisterCollider( this,
													  CollisionSystem::CollisionFilter::Projectile,
													  CollisionSystem::CollisionFilter::Character
	);
}

void FireballProjectile::OnOverlap( OverlapEvent& e )
{
	if ( e.GetTarget().GetID() == C_Engine::GetEntityManager()->GetObject( "player1" )->GetID() )
		C_Engine::GetEntityManager()->RemoveObject( GetID() );
}

float FireballProjectile::GetDamage()
{
	return m_damage;
}

//===================================================================================================
Actor* FireballProjectile::CreateLeft( std::string id )
{

	sf::Texture& fireballLeft = C_Engine::GetTextureManager()->GetTexture( g_texFilepaths.at( ecTexture::FIREBALL_MIRROR ) );

	return new FireballProjectile( id,
									FIREBALL_SPEED,
									ActorDirection::LEFT,
									sf::Sprite( fireballLeft, sf::IntRect( { 247,0 }, { 80,80 } ) )
								 );
}


//===================================================================================================
Actor* FireballProjectile::CreateRight( std::string id )
{
	sf::Texture& fireballRight = C_Engine::GetTextureManager()->GetTexture( g_texFilepaths.at( ecTexture::FIREBALL ) );
	return new FireballProjectile( id,
									FIREBALL_SPEED,
									ActorDirection::RIGHT,
									sf::Sprite( fireballRight, sf::IntRect( { 0,0 }, { 80,80 } ) )
	);
}

