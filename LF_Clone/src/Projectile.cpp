#include "Projectile.h"


// =================================================================================
Projectile::Projectile( std::string id ) : Actor( id )
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


// =================================================================================
Actor* Projectile::Create( std::string id )
{
	return new Projectile( id );
}
