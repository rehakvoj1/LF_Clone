#pragma once

#include <unordered_map>

#include "imgui-SFML.h"
#include "imgui.h"
#include <SFML/Graphics.hpp>

#include "Types.h"
#include "Projectile.h"

class Enemy
{

public:
	explicit Enemy( sf::Sprite& spriteDefault );
	explicit Enemy( sf::Sprite& spriteDefault, sf::Sprite& spriteMirror );

	void		OnUpdate( float dt );
	void		OnRender( sf::RenderWindow& window );


	sf::Sprite& GetCurrentSprite();
	int			GetDirection();
	Projectile& GetProjectile();

	
	void SetProjectile( SpriteOrientation so, sf::Sprite sprite, float speed, float duration, float cooldown );
	void TakeDamage( float damage );

private:
	std::unordered_map<SpriteOrientation, sf::Sprite> m_enemySprites;
	SpriteOrientation m_currSprite;
	ImVec2 m_pos;
	float m_health;
	float m_speed;
	Projectile m_fireball; /* Should be independent of Enemy -> now updating of enemy updates projectile */
};

