#pragma once

#include "Actor.h"

class Player : public Actor
{
public:
	Player( std::string id );

	virtual void OnUpdate( float dt ) override;
	virtual void OnRender() override;


	static Actor* Create( std::string id );

private:
};
