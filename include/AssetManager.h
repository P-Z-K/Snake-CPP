#pragma once

#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <memory>
#include <map>

enum class TextureType
{
	WALL,
	GRASS,
	SNAKETAIL,
	SNAKEHEAD,
	APPLE,
	CHERRY,
	WATERMELON,
	KIWI
};


enum class FontType
{
	PRIMARYFONT
};

enum class SoundType
{
	SOUNDTRACK,
	HIT,
	GAMEOVER
};


class AssetManager
{
public:
	AssetManager();

private:
	std::map<TextureType, std::unique_ptr<sf::Texture>> m_textures;
	std::map<FontType, std::unique_ptr<sf::Font>>		m_fonts;
	std::map<SoundType, std::unique_ptr<sf::SoundBuffer>>     m_sounds;

public:
	void loadTexture(const std::string& filePath, TextureType type, bool isRepeated = false);
	void loadFont(const std::string& filePath, FontType type);
	void loadSoundBuffer(const std::string& filePath, SoundType type);
	std::unique_ptr<sf::Music> getSoundtrack(const std::string& filePath);

public:
	const sf::Texture& getTexture(TextureType type) const;
	const sf::Font&	 getFont(FontType type) const;
	const sf::SoundBuffer& getSound(SoundType type) const;
};

