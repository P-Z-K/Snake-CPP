#include "Snake.h"

Snake::Snake() :
	// TODO: Remove magic number
	m_snakeBody(std::vector<sf::Sprite>(6)),
	m_head(m_snakeBody.begin())
{
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

void Snake::move(SnakeDirection newDir)
{
	for (size_t i = m_snakeBody.size() - 1; i > 0; --i)
	{
		m_snakeBody[i].setPosition(m_snakeBody[i - 1].getPosition());
	}

	std::unique_ptr<sf::Vector2f> offset = dirToVector(newDir);

	m_head->move(*offset);
}

void Snake::initPosition()
{
	// TODO: Remove magic numbers
	m_head->setPosition(48.f, 48.f);
	
	float tailXPos = 32.f;

	for (size_t i = 1; i < m_snakeBody.size(); ++i)
	{
		m_snakeBody[i].setPosition(tailXPos, 48.f);
		tailXPos -= 16.f;
	}
}

std::unique_ptr<sf::Vector2f> Snake::dirToVector(SnakeDirection dir)
{
	// TODO: Remove magic numbers
	switch (dir)
	{
	case SnakeDirection::UP:
		return std::make_unique<sf::Vector2f>(0.f, -16.f);
		break;
	case SnakeDirection::DOWN:
		return std::make_unique<sf::Vector2f>(0.f, 16.f);
		break;
	case SnakeDirection::LEFT:
		return std::make_unique<sf::Vector2f>(-16.f, 0.f);
		break;
	case SnakeDirection::RIGHT:
		return std::make_unique<sf::Vector2f>(16.f, 0.f);
		break;
	default:
		break;
	}
}
