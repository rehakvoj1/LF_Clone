#pragma once
#include "Actor.h"
#include <SFML/Graphics.hpp>

class Projectile : public Actor
{
public:

	enum ProjectileDirection
	{
		LEFT = -1,
		INVALID = 0,
		RIGHT = 1
	};


public:
	explicit Projectile( std::string id, float speed, ProjectileDirection dir, sf::Sprite sprite );

	virtual void OnUpdate( float dt ) override;
	virtual void OnRender() override;

protected:
	float m_speed;
	ProjectileDirection m_dir;
	sf::Sprite m_sprite;


private:
};

