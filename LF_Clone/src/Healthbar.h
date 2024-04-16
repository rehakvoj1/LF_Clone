#pragma once

#include "Actor.h"

#include "imgui.h"

#include <string>

class Healthbar : public Actor
{
public:
	Healthbar(std::string id, ImVec2 topLeft, ImVec2 size );
	virtual ~Healthbar();


	virtual void OnUpdate( float dt ) override;
	virtual void OnRender() override;

	virtual ImVec2 GetPivot() override;
	virtual sf::Drawable* GetDrawable() override;

	

protected:
	float m_health;
	ImVec2 m_topLeft;
	ImVec2 m_size;
};

