#pragma once

#include <unordered_map>

#include "imgui-SFML.h"
#include "imgui.h"
#include <SFML/Graphics.hpp>

#include "Types.h"
#include "Projectile.h"

class Player
{
public:
	explicit Player( sf::Sprite& spriteDefault, sf::Sprite& spriteMirror ); 
		

	void OnUpdate( float dt );
	void OnRender( sf::RenderWindow& window );

	void TakeDamage( float damage );
	
	sf::Sprite& GetCurrentSprite();
	int			GetDirection();
	float		GetHealth();
	Projectile& GetProjectile();

	void		SetHealth( float val );
	void		SetProjectile( SpriteOrientation so, sf::Sprite, float speed, float duration, float cooldown );

private:
	std::unordered_map<SpriteOrientation, sf::Sprite> m_playerSprites;
	SpriteOrientation m_currSprite;
	ImVec2 m_pos;
	float m_health;
	float m_speed;
	Projectile m_frostbolt; /* Should be independent of Player -> now updating of player updates projectile */
};

