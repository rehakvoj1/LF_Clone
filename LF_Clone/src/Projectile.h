#pragma once
#include "Actor.h"
#include <SFML/Graphics.hpp>

const float PROJECTILE_DURATION_IN_SECS = 4.0f;


class Projectile : public Actor
{
public:
	explicit Projectile( std::string id, float speed, ActorDirection dir, sf::Sprite sprite );
	virtual ~Projectile();

	virtual void OnUpdate( float dt ) override;
	virtual void OnRender() override;
	virtual void OnCreate() override;




	virtual sf::Drawable* GetDrawable() override;
	virtual ImVec2 GetPivot() override;

	

	void SetPosition( ImVec2 newPos );

protected:
	float m_speed;
	ActorDirection m_dir;
	sf::Sprite m_sprite;
	ImVec2 m_pos;
	float m_durationInSecs;
	sf::Clock m_timer;
	

private:
};

