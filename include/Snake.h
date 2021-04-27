#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

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

	const std::vector<sf::Sprite>& GetBody() const;

	void Init(const sf::Texture& head, const sf::Texture& tail);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void Move(SnakeDirection newDir);
	void Grow();
	bool IsOn(const sf::Sprite& other) const;
	bool IsSelfIntersects() const;

private:
	void InitPosition();
	static sf::Vector2f DirToVector(SnakeDirection dir);
};

