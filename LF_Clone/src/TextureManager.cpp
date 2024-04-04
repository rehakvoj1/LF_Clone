#include "TextureManager.h"

#include <iostream>


//===================================================================================================
TextureManager* TextureManager::Create()
{
	return new TextureManager;
}


//===================================================================================================
sf::Texture& TextureManager::GetTexture( std::string filepath )
{
	auto it = m_textures.find( filepath );
	if ( it != m_textures.end() )	// texture found in map
	{
		return *(it->second);
	}
	else	// texture not found in map
	{
		sf::Texture* tex = new sf::Texture;
		if ( !tex->loadFromFile( filepath ) )	// failed to load image from the path
		{
			std::cout << "Failed to load image from path: " << filepath << std::endl;
			// TODO: Return REPLACEME texture
		}
		else
		{
			return *(m_textures.emplace( filepath, tex ).first->second);	// returns inserted texture or existing texture with same key(=filepath)
		}
	}
}
