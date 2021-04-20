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

public:
	Snake();

public:
	const std::vector<sf::Sprite>& getBody() const;

public:
	void init(const sf::Texture& head, const sf::Texture& tail);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void move(SnakeDirection newDir);
	void grow();
	bool isOn(const sf::Sprite& other) const;
	bool isSelfIntersects() const;

private:
	void initPosition();
	sf::Vector2f dirToVector(SnakeDirection dir);
};

