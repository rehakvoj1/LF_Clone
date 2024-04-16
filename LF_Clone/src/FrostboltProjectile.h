#pragma once
#include "Projectile.h"

const float FROSTBOLT_SPEED = 150.0f;


class FrostboltProjectile : public Projectile
{
public:
	FrostboltProjectile( std::string id, float speed, ActorDirection dir, sf::Sprite sprite );
	virtual ~FrostboltProjectile();

	virtual void OnCreate() override;

	void OnOverlap( OverlapEvent& e );


	static Actor* CreateLeft( std::string id );
	static Actor* CreateRight( std::string id );

private:

};

