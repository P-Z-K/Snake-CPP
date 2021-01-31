#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

class Snake : public sf::Drawable
{
private:
	std::vector<sf::Sprite> m_snakeBody;
	sf::Texture m_tailTexture;
	std::vector<sf::Sprite>::iterator m_head;

public:
	Snake();

public:
	void init(const sf::Texture& head, const sf::Texture& tail);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void initPosition();
};

