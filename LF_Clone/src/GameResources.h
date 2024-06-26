#pragma once

#include <unordered_map>
#include <string>

enum class ecTexture
{
	SORCERER,
	SORCERER_MIRROR,
	FROSTBOLT,
	FROSTBOLT_MIRROR,
	ENEMY,
	ENEMY_MIRROR,
	FIREBALL,
	FIREBALL_MIRROR
};



const std::unordered_map<ecTexture, std::string> g_texFilepaths
{
	{ecTexture::SORCERER, "./resource/sorcerer_0b.png"},
	{ecTexture::SORCERER_MIRROR, "./resource/sorcerer_0b_mirror.png"},
	{ecTexture::FROSTBOLT, "./resource/freeze_ball.png"},
	{ecTexture::FROSTBOLT_MIRROR, "./resource/freeze_ball_mirror.png"},
	{ecTexture::ENEMY, "./resource/firen_0.png"},
	{ecTexture::ENEMY_MIRROR, "./resource/firen_0_mirror.png"},
	{ecTexture::FIREBALL, "./resource/firen_ball.png"},
	{ecTexture::FIREBALL_MIRROR, "./resource/firen_ball_mirror.png"}
};


