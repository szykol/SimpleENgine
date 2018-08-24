#include "ResourceManager.h"

namespace sen {
	SFMLCacheSystem ResourceManager::m_cache;
	SFMLAudioProvider ResourceManager::m_audioProvider(ResourceManager::m_cache);
	const sf::Font& ResourceManager::getFont(const std::string & pathFile)
	{
		auto font = m_cache.get<sf::Font>(pathFile); 
		if(font)
			return *font;
		else
			return *m_cache.get<sf::Font>("Fonts/Roboto.ttf");
	}
	const sf::Texture & ResourceManager::getTexture(const std::string & pathFile)
	{
		auto texture = m_cache.get<sf::Texture>(pathFile);
		if(texture)
			return *texture;
		else
			return *m_cache.get<sf::Texture>("Images/error.png");
	}
}