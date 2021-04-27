#include "AssetManager.h"

#include <iostream>

AssetManager::AssetManager() :
	m_textures(),
	m_fonts()
{
}

void AssetManager::LoadTexture(const std::string& filePath, TextureType type, const bool isRepeated)
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

void AssetManager::LoadFont(const std::string& filePath, FontType type)
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

void AssetManager::LoadSoundBuffer(const std::string& filePath, SoundType type)
{
	auto soundBuffer = std::make_unique<sf::SoundBuffer>();

	if (soundBuffer->loadFromFile(filePath))
	{
		m_sounds.emplace(type, std::move(soundBuffer));
	}
	else
	{
		std::cout << "Sound " << filePath << " not loaded!\n";
	}
}

std::unique_ptr<sf::Music> AssetManager::GetSoundtrack(const std::string& filePath) const
{
	auto music = std::make_unique<sf::Music>();

	if (!music->openFromFile(filePath))
	{
		std::cout << "Soundtrack not loaded!";
		return nullptr;
	}

	return music;
}


