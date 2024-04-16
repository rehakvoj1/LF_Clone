#pragma once

#include <string>

#include "imgui.h"
#include "SFML/Graphics/Drawable.hpp"

#include "GameObject.h"
#include "I_Listener.h"
#include "I_Publisher.h"

class Actor :	public GameObject,
				public I_Listener,
				public I_Publisher
{
public:
	enum ActorDirection
	{
		LEFT = -1,
		INVALID = 0,
		RIGHT = 1
	};


public:
	Actor( std::string id ) : GameObject( id )
	{
	}

	virtual ~Actor();

	virtual void OnUpdate(float dt) = 0;
	virtual void OnRender() = 0;
	virtual void OnCreate() = 0;

	virtual ImVec2  GetPivot() = 0;
	virtual sf::Drawable* GetDrawable() = 0;

	virtual AABB2D* GetAABB2D() override;

protected:
	AABB2D m_bbox;
};