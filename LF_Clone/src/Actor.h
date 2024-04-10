#pragma once

#include <string>

#include "GameObject.h"
#include "I_Listener.h"
#include "I_Publisher.h"

class Actor :	public GameObject,
				public I_Listener,
				public I_Publisher
{
public:
	Actor( std::string id ) : GameObject( id )
	{
	}

	virtual void OnUpdate(float dt) = 0;
	virtual void OnRender() = 0;
	
	virtual AABB2D* GetAABB2D() override;

protected:
	AABB2D m_bbox;
};