#pragma once

#include <string>

#include "GameObject.h"

class Actor : public GameObject
{
public:
	Actor( std::string id ) : GameObject( id )
	{
	}

	virtual void OnUpdate()
	{
	}
	virtual void OnRender()
	{
	}

protected:
};