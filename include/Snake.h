#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Settings.h"

enum class SnakeDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Snake : public sf::Drawable
{
private:
	std::vector<sf::Sprite> m_snakeBody;
	std::vector<sf::Sprite>::iterator m_head;
	sf::Vector2f m_gridStartPos;

public:
	Snake();

public:
	void init(const sf::Texture& head, const sf::Texture& tail);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void move(SnakeDirection newDir);
	bool isOn(const sf::Sprite& other) const;
	bool isSelfIntersects() const;

private:
	void initPosition();
	std::unique_ptr<sf::Vector2f> dirToVector(SnakeDirection dir);
};

