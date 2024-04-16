#pragma once

#include "SFML\Graphics.hpp"

#include "Actor.h"
#include "PlayerHealthbar.h"

const float PLAYER_SPEED = 150.0f;
const int STARTING_FROSTBOLT_OFFSET_X = 10;
const int STARTING_FROSTBOLT_OFFSET_Y = 5;


class Player : public Actor
{
public:
	Player( std::string id, float speed, ActorDirection dir, sf::Sprite sprLeft, sf::Sprite sprRight );

	virtual void OnUpdate( float dt ) override;
	virtual void OnRender() override;
	virtual void OnCreate() override;
	
	virtual ImVec2 GetPivot() override;
	virtual sf::Drawable* GetDrawable() override;


	static Actor* CreateSorcerer( std::string id );


private:
	void TakeDamage( float damage );

private:

	enum PlayerState
	{
		NO_MOVE = 0,
		MOVE_UP = 1,
		MOVE_DOWN = 2,
		MOVE_LEFT = 4,
		MOVE_RIGHT = 8
	};


	bool IsMovingUp() const;
	bool IsMovingDown() const;
	bool IsMovingLeft() const;
	bool IsMovingRight() const;
	

	void OnKeyPressed( KeyPressedEvent& e );
	void OnKeyReleased( KeyReleasedEvent& e );
	void OnOverlap( OverlapEvent& e );
	void OnProjectileDestroyed( ProjectileDestroyedEvent& e );
	
	friend void PlayerHealthbar::OnPlayerHit( HitEvent& e );


	sf::Sprite m_sprites[2];
	ActorDirection m_dir;
	float m_speed;
	ImVec2 m_pos;
	PlayerState m_state;
	float m_health;
	bool m_isSpellReady;
};
