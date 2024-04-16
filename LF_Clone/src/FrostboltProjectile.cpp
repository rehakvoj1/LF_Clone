#include "FrostboltProjectile.h"
#include "C_Engine.h"
#include "TextureManager.h"
#include "GameResources.h"
#include "CollisionSystem.h"
#include "EntityManager.h"

//===================================================================================================
FrostboltProjectile::FrostboltProjectile( std::string id, float speed, ActorDirection dir, sf::Sprite sprite ) :
	Projectile( id, speed, dir, sprite )
{
}

FrostboltProjectile::~FrostboltProjectile()
{

}

void FrostboltProjectile::OnCreate()
{
	Projectile::OnCreate();

	Observe<OverlapEvent>( C_Engine::GetCollisionSystem(), &FrostboltProjectile::OnOverlap );
	C_Engine::GetCollisionSystem()->RegisterCollider( this,
													  CollisionSystem::CollisionFilter::Projectile,
													  CollisionSystem::CollisionFilter::Character
	);
}

void FrostboltProjectile::OnOverlap( OverlapEvent& e )
{
	if ( e.GetTarget().GetID() == C_Engine::GetEntityManager()->GetObject( "enemy" )->GetID() )
		C_Engine::GetEntityManager()->RemoveObject( GetID() );
}


//===================================================================================================
Actor* FrostboltProjectile::CreateLeft( std::string id )
{
	
	sf::Texture& frostboltLeft = C_Engine::GetTextureManager()->GetTexture( g_texFilepaths.at( ecTexture::FROSTBOLT_MIRROR ) );

	return new FrostboltProjectile	(	id,
										FROSTBOLT_SPEED,
										ActorDirection::LEFT,
										sf::Sprite( frostboltLeft, sf::IntRect( { 247,0 }, { 80,80 } ) )
									);
}


//===================================================================================================
Actor* FrostboltProjectile::CreateRight( std::string id )
{
	sf::Texture& frostboltRight = C_Engine::GetTextureManager()->GetTexture( g_texFilepaths.at( ecTexture::FROSTBOLT ) );
	return new FrostboltProjectile( id,
									FROSTBOLT_SPEED,
									ActorDirection::RIGHT,
									sf::Sprite( frostboltRight, sf::IntRect( { 0,0 }, { 80,80 } ) )
	);
}
