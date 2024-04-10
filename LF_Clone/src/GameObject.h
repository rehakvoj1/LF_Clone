#pragma once

#include <string>

#include "AABB.h"

class GameObject
{
public:
	GameObject( std::string id );
	std::string& GetID();

	virtual AABB2D* GetAABB2D() = 0;

protected:
	std::string m_ID;	// bad choice -> better some GUID number
};