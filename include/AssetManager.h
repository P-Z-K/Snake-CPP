#pragma once

#include <SFML\Graphics.hpp>

#include <iostream>
#include <map>

enum class TextureType
{
	WALL,
	GRASS,
	SNAKETAIL,
	SNAKEHEAD
};


enum class FontType
{
	PRIMARYFONT
};


class AssetManager
{
public:
	AssetManager();
	~AssetManager();

private:
	std::map<TextureType, std::unique_ptr<sf::Texture>> m_textures;
	std::map<FontType, std::unique_ptr<sf::Font>>		m_fonts;

public:
	void loadTexture(const std::string& filePath, TextureType type, bool isRepeated = false);
	void loadFont(const std::string& filePath, FontType type);

public:
	const sf::Texture& getTexture(TextureType type) const;
	const sf::Font&	 getFont(FontType type) const;
};

