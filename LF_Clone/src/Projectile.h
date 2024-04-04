#pragma once
#include "Actor.h"
class Projectile : public Actor
{
public:
	Projectile( std::string id );

	virtual void OnUpdate( float dt ) override;
	virtual void OnRender() override;


	static Actor* Create( std::string id );

private:
};

