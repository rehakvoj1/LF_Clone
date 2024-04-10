#pragma once
#include "Projectile.h"

const float FIREBALL_SPEED = 250.0f;

class FireballProjectile : public Projectile
{
public:
	FireballProjectile( std::string id, float speed, ProjectileDirection dir, sf::Sprite sprite );


	static Actor* CreateLeft( std::string id );
	static Actor* CreateRight( std::string id );

private:
};

