#include "FireballProjectile.h"
#include "C_Engine.h"
#include "TextureManager.h"
#include "GameResources.h"


//===================================================================================================
FireballProjectile::FireballProjectile( std::string id, float speed, ProjectileDirection dir, sf::Sprite sprite ) :
	Projectile( id, speed, dir, sprite )
{
}



//===================================================================================================
Actor* FireballProjectile::CreateLeft( std::string id )
{

	sf::Texture& fireballLeft = C_Engine::GetTextureManager()->GetTexture( g_texFilepaths.at( ecTexture::FIREBALL_MIRROR ) );

	return new FireballProjectile( id,
									FIREBALL_SPEED,
									ProjectileDirection::LEFT,
									sf::Sprite( fireballLeft, sf::IntRect( { 247,0 }, { 80,80 } ) )
	);
}


//===================================================================================================
Actor* FireballProjectile::CreateRight( std::string id )
{
	sf::Texture& fireballRight = C_Engine::GetTextureManager()->GetTexture( g_texFilepaths.at( ecTexture::FIREBALL ) );
	return new FireballProjectile( id,
									FIREBALL_SPEED,
									ProjectileDirection::RIGHT,
									sf::Sprite( fireballRight, sf::IntRect( { 0,0 }, { 80,80 } ) )
	);
}

