#pragma once
#include "Projectile.h"

const float FIREBALL_SPEED = 350.0f;
const float FIREBALL_DAMAGE = 20.0f;

class FireballProjectile : public Projectile
{
public:
	FireballProjectile( std::string id, float speed, ActorDirection dir, sf::Sprite sprite );
	virtual ~FireballProjectile();

	virtual void OnCreate() override;

	void OnOverlap( OverlapEvent& e );

	float GetDamage();

	static Actor* CreateLeft( std::string id );
	static Actor* CreateRight( std::string id );

private:
	float m_damage;
};

