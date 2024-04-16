#pragma once
#include "Actor.h"

#include "SFML/Graphics.hpp"


const float ENEMY_SPEED = 35.0f;
const int STARTING_FIREBALL_OFFSET_X = 10;
const int STARTING_FIREBALL_OFFSET_Y = 5;


class Enemy : public Actor
{
public:
	Enemy( std::string id, float speed, ActorDirection dir, sf::Sprite sprLeft, sf::Sprite sprRight );


	virtual void OnUpdate( float dt ) override;
	virtual void OnRender() override;
	virtual void OnCreate() override;

	void OnOverlap( OverlapEvent& e );
	void OnProjectileDestroyed( ProjectileDestroyedEvent& e );


	virtual sf::Drawable* GetDrawable() override;
	virtual ImVec2 GetPivot() override;

	static Actor* Create( std::string id );
private:

	sf::Sprite m_sprites[2];
	float m_speed;
	ActorDirection m_dir;
	ImVec2 m_pos;
	bool m_isSpellReady;
};

