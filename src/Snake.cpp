#include "Snake.h"

Snake::Snake() :
	m_snakeBody(std::vector<sf::Sprite>(Settings::SNAKE_START_LENGTH))
{
	m_snakeBody.reserve(20); // TODO: Need to create custom allocator
	m_head = m_snakeBody.begin();
}

void Snake::init(const sf::Texture& head, const sf::Texture& tail)
{
	m_head->setTexture(head);

	// First element of the vector is head, thus we start from index 1
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

	sf::Vector2f offset = dirToVector(newDir);

	m_head->move(offset);
}

void Snake::grow()
{
	size_t oldCapacity = m_snakeBody.capacity();

	// Add one piece of snake's body with the tail texture
	m_snakeBody.emplace_back(*m_snakeBody[1].getTexture());

	// Vector reallocated memory, so we give iterator new address 
	if (m_snakeBody.capacity() > oldCapacity)
	{
		m_head = m_snakeBody.begin();
		std::cout << "Vector reallocated memory\n";
	}
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

const std::vector<sf::Sprite>& Snake::getBody() const
{
	return m_snakeBody;
}

void Snake::initPosition()
{
	using Settings::UNIT;
	using Settings::SNAKE_START_POS;

	m_head->setPosition((float)UNIT * SNAKE_START_POS.x, (float)UNIT * SNAKE_START_POS.y);

	// Snake's body is the straight line on x axis
	float tailXPos = m_head->getPosition().x - UNIT;
	for (size_t i = 1; i < m_snakeBody.size(); ++i)
	{
		m_snakeBody[i].setPosition(tailXPos, m_head->getPosition().y);
		tailXPos -= UNIT;
	}
}

sf::Vector2f Snake::dirToVector(SnakeDirection dir)
{
	using Settings::UNIT;

	switch (dir)
	{
	case SnakeDirection::UP:
		return sf::Vector2f(0.f, (float)-UNIT);
		break;
	case SnakeDirection::DOWN:
		return sf::Vector2f(0.f, (float)UNIT);
		break;
	case SnakeDirection::LEFT:
		return sf::Vector2f((float)-UNIT, 0.f);
		break;
	case SnakeDirection::RIGHT:
		return sf::Vector2f((float)UNIT, 0.f);
		break;
	default:
		break;
	}
}
