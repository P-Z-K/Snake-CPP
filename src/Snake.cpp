#include "Snake.h"

Snake::Snake() :
	m_snakeBody(std::vector<sf::Sprite>(3))
{
	m_head = m_snakeBody.begin();
}

void Snake::init(const sf::Texture& head, const sf::Texture& tail)
{
	m_tailTexture = tail;

	m_head->setTexture(head);

	// First element of the vector is head, thus we start from 1 index
	for (size_t i = 1; i < m_snakeBody.size(); ++i)
	{
		m_snakeBody[i].setTexture(m_tailTexture);
	}

	initPosition();
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& piece : m_snakeBody)
	{
		target.draw(piece);
	}
}

void Snake::initPosition()
{
	m_head->setPosition(48.f, 48.f);
	
	float tailXPos = 32.f;

	for (size_t i = 1; i < m_snakeBody.size(); ++i)
	{
		m_snakeBody[i].setPosition(tailXPos, 48.f);
		tailXPos -= 16.f;
	}
}
