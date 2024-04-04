#pragma once
#include "Actor.h"


class Enemy : public Actor
{
public:
	Enemy( std::string id );


	virtual void OnUpdate( float dt ) override;
	virtual void OnRender() override;

	static Actor* Create( std::string id );
private:
};

