#include "AssetManager.h"

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{

}

void AssetManager::loadTexture(const std::string& filePath, TextureType type, bool isRepeated)
{
	auto texture = std::make_unique<sf::Texture>();

	if (texture->loadFromFile(filePath))
	{
		texture->setRepeated(isRepeated);
		m_textures.emplace(type, std::move(texture));
	}
	else
	{
		std::cout << "Texture " << filePath << " not loaded!\n";
	}
}

void AssetManager::loadFont(const std::string& filePath, FontType type)
{
	auto font = std::make_unique<sf::Font>();

	if (font->loadFromFile(filePath))
	{
		m_fonts.emplace(type, std::move(font));
	}
	else
	{
		std::cout << "Font " << filePath << " not loaded!\n";
	}
}

const sf::Texture& AssetManager::getTexture(TextureType type) const
{
	return *(m_textures.at(type).get());
}

const sf::Font& AssetManager::getFont(FontType type) const
{
	return *(m_fonts.at(type).get());
}


