#pragma once

#include <string>

#include "GameObject.h"

class Actor : public GameObject
{
public:
	Actor( std::string id ) : GameObject( id )
	{
	}

	virtual void OnUpdate(float dt) = 0;
	virtual void OnRender() = 0;
	
protected:
};