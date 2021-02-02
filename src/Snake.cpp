#include "Snake.h"

Snake::Snake() :
	// TODO: Remove magic number
	m_snakeBody(std::vector<sf::Sprite>(START_SNAKE_LENGTH)),
	m_head(m_snakeBody.begin()),
	m_gridStartPos(GRID_START_POS.x, GRID_START_POS.y)
{
}

void Snake::init(const sf::Texture& head, const sf::Texture& tail)
{
	m_head->setTexture(head);

	// First element of the vector is head, thus we start from 1 index
	for (size_t i = 1; i < m_snakeBody.size(); ++i)
	{
		m_snakeBody[i].setTexture(tail);
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
	m_head->setPosition(CELL_SIZE * m_gridStartPos.x, CELL_SIZE * m_gridStartPos.y);

	// Snake's body is the straight line on x axis
	float tailXPos = m_head->getPosition().x - CELL_SIZE;
	for (size_t i = 1; i < m_snakeBody.size(); ++i)
	{
		m_snakeBody[i].setPosition(tailXPos, m_head->getPosition().y);
		tailXPos -= CELL_SIZE;
	}
}

std::unique_ptr<sf::Vector2f> Snake::dirToVector(SnakeDirection dir)
{
	switch (dir)
	{
	case SnakeDirection::UP:
		return std::make_unique<sf::Vector2f>(0.f, -CELL_SIZE);
		break;
	case SnakeDirection::DOWN:
		return std::make_unique<sf::Vector2f>(0.f, CELL_SIZE);
		break;
	case SnakeDirection::LEFT:
		return std::make_unique<sf::Vector2f>(-CELL_SIZE, 0.f);
		break;
	case SnakeDirection::RIGHT:
		return std::make_unique<sf::Vector2f>(CELL_SIZE, 0.f);
		break;
	default:
		break;
	}
}
