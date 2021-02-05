#include "Snake.h"

Snake::Snake() :
	m_snakeBody(std::vector<sf::Sprite>(Settings::START_SNAKE_LENGTH)),
	m_head(m_snakeBody.begin()),
	m_gridStartPos(Settings::GRID_START_POS.x, Settings::GRID_START_POS.y)
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

/* TODO: Need to fix snake's movement bug. 
	When you press fastly up or down key and 
	then immediately press right or left key(depends on the current snake's direction), 
	snake will make illegal move(turn around in place) */
void Snake::move(SnakeDirection newDir)
{
	for (size_t i = m_snakeBody.size() - 1; i > 0; --i)
	{
		m_snakeBody[i].setPosition(m_snakeBody[i - 1].getPosition());
	}

	std::unique_ptr<sf::Vector2f> offset = dirToVector(newDir);

	m_head->move(*offset);
}

bool Snake::isOn(const sf::Sprite& other) const
{
	return m_head->getGlobalBounds().intersects(other.getGlobalBounds());
}

bool Snake::isSelfIntersects() const
{
	for (size_t i = 1; i < m_snakeBody.size(); ++i)
	{
		if (m_head->getGlobalBounds().intersects(m_snakeBody[i].getGlobalBounds()))
			return true;
	}

	return false;
}

void Snake::initPosition()
{
	using Settings::UNIT;

	m_head->setPosition(UNIT * m_gridStartPos.x, UNIT * m_gridStartPos.y);

	// Snake's body is the straight line on x axis
	float tailXPos = m_head->getPosition().x - UNIT;
	for (size_t i = 1; i < m_snakeBody.size(); ++i)
	{
		m_snakeBody[i].setPosition(tailXPos, m_head->getPosition().y);
		tailXPos -= UNIT;
	}
}

std::unique_ptr<sf::Vector2f> Snake::dirToVector(SnakeDirection dir)
{
	using Settings::UNIT;

	switch (dir)
	{
	case SnakeDirection::UP:
		return std::make_unique<sf::Vector2f>(0.f, -UNIT);
		break;
	case SnakeDirection::DOWN:
		return std::make_unique<sf::Vector2f>(0.f, UNIT);
		break;
	case SnakeDirection::LEFT:
		return std::make_unique<sf::Vector2f>(-UNIT, 0.f);
		break;
	case SnakeDirection::RIGHT:
		return std::make_unique<sf::Vector2f>(UNIT, 0.f);
		break;
	default:
		break;
	}
}
