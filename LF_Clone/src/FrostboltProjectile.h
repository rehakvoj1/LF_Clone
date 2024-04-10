#pragma once
#include "Projectile.h"

const float FROSTBOLT_SPEED = 50.0f;


class FrostboltProjectile : public Projectile
{
public:
	FrostboltProjectile( std::string id, float speed, ProjectileDirection dir, sf::Sprite sprite );


	static Actor* CreateLeft( std::string id );
	static Actor* CreateRight( std::string id );

private:

};

