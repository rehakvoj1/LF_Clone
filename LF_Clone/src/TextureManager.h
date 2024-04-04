#pragma once

#include <unordered_map>
#include <string>

#include <SFML/Graphics.hpp>

class TextureManager
{
public:
	static TextureManager* Create();

	sf::Texture& GetTexture( std::string filepath );

private:
	std::unordered_map<std::string, sf::Texture*> m_textures;
};

