#include "FrostboltProjectile.h"
#include "C_Engine.h"
#include "TextureManager.h"
#include "GameResources.h"

FrostboltProjectile::FrostboltProjectile( std::string id, float speed, ProjectileDirection dir, sf::Sprite sprite ) :
	Projectile( id, speed, dir, sprite )
{
}



Actor* FrostboltProjectile::CreateLeft( std::string id )
{
	
	sf::Texture& frostboltLeft = C_Engine::GetTextureManager()->GetTexture( g_texFilepaths.at( ecTexture::FROSTBOLT_MIRROR ) );

	return new FrostboltProjectile	(	id,
										FROSTBOLT_SPEED,
										ProjectileDirection::LEFT,
										sf::Sprite( frostboltLeft, sf::IntRect( { 247,0 }, { 80,80 } ) )
									);
}

Actor* FrostboltProjectile::CreateRight( std::string id )
{
	sf::Texture& frostboltRight = C_Engine::GetTextureManager()->GetTexture( g_texFilepaths.at( ecTexture::FROSTBOLT ) );
	return new FrostboltProjectile( id,
									FROSTBOLT_SPEED,
									ProjectileDirection::RIGHT,
									sf::Sprite( frostboltRight, sf::IntRect( { 0,0 }, { 80,80 } ) )
	);
}
