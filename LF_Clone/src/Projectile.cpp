#include "Projectile.h"


// =================================================================================
Projectile::Projectile( std::string id, float speed, ProjectileDirection dir, sf::Sprite sprite ) : 
	Actor( id ),
	m_speed( speed ),
	m_dir( dir ),
	m_sprite( sprite )

{
}

// =================================================================================
void Projectile::OnUpdate( float dt )
{
}

// =================================================================================
void Projectile::OnRender()
{
}