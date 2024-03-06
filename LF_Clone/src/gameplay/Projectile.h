#pragma once

#include <unordered_map>

#include "imgui-SFML.h"
#include "imgui.h"
#include <SFML/Graphics.hpp>

#include "Types.h"

class Projectile
{
public:
	Projectile();
	Projectile( sf::Sprite& spriteDefault );
	Projectile( sf::Sprite& spriteDefault, sf::Sprite& spriteMirror );

	void Cast(ImVec2 startLoc, SpriteOrientation casterDir);
	void ResetTimer();
	void OnUpdate( float dt );

	sf::Time GetElapsedTime();
	ImVec2 GetPosition();
	int GetDirection();
	float GetCooldown();
	sf::Sprite& GetCurrentSprite();
	bool IsCasted();

	void AddSprite( sf::Sprite sprite, SpriteOrientation spriteOrientation );
	void SetSprite( SpriteOrientation spriteOrientation );
	void SetSpeed( float speed );
	void SetDuration( float duration );
	void SetCooldown( float cooldown );
	void SetPosition( ImVec2 pos );
	void SetCollision( bool );

private:
	std::unordered_map<SpriteOrientation, sf::Sprite> m_projectileSprites;
	SpriteOrientation m_currSprite;
	ImVec2 m_pos;
	float m_speed;
	float m_duration;
	bool m_collided;
	bool m_isCasted;
	float m_cooldown;
	sf::Clock m_timer;  // measures both -> cooldown and duration
};

