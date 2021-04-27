#include <iostream>

#include "Snake.h"
#include "Settings.h"


Snake::Snake() :
	m_snakeBody(std::vector<sf::Sprite>(Settings::Snake_Start_Length))
{
	m_snakeBody.reserve(32);
	m_head = m_snakeBody.begin();
}

void Snake::Init(const sf::Texture& head, const sf::Texture& tail)
{
	m_head->setTexture(head);

	// First element of the vector is head, thus we start from index 1
	for (size_t i = 1; i < m_snakeBody.size(); ++i)
	{
		m_snakeBody[i].setTexture(tail);
	}

	InitPosition();
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& piece : m_snakeBody)
	{
		target.draw(piece);
	}
}

void Snake::Move(SnakeDirection newDir)
{
	for (size_t i = m_snakeBody.size() - 1; i > 0; --i)
	{
		m_snakeBody[i].setPosition(m_snakeBody[i - 1].getPosition());
	}

	const sf::Vector2f offset = DirToVector(newDir);

	m_head->move(offset);
}

void Snake::Grow()
{
	const size_t oldCapacity = m_snakeBody.capacity();

	// Add one piece of snake's body with the tail texture
	m_snakeBody.emplace_back(*m_snakeBody[1].getTexture());

	// Vector reallocated memory, so we give iterator new address 
	if (m_snakeBody.capacity() > oldCapacity)
	{
		m_head = m_snakeBody.begin();
		std::cout << "Vector reallocated memory\n";
	}
}

bool Snake::IsOn(const sf::Sprite& other) const
{
	return m_head->getGlobalBounds().intersects(other.getGlobalBounds());
}

bool Snake::IsSelfIntersects() const
{
	for (size_t i = 1; i < m_snakeBody.size(); ++i)
	{
		if (m_head->getGlobalBounds().intersects(m_snakeBody[i].getGlobalBounds()))
			return true;
	}

	return false;
}

const std::vector<sf::Sprite>& Snake::GetBody() const
{
	return m_snakeBody;
}

void Snake::InitPosition()
{
	using Settings::Unit;
	using Settings::Snake_Start_Pos;

	m_head->setPosition(static_cast<float>(Unit) * Snake_Start_Pos.m_x, static_cast<float>(Unit) * Snake_Start_Pos.m_y);

	// Snake's body is the straight line on x axis
	float tailXPos = m_head->getPosition().x - Unit;
	for (size_t i = 1; i < m_snakeBody.size(); ++i)
	{
		m_snakeBody[i].setPosition(tailXPos, m_head->getPosition().y);
		tailXPos -= Unit;
	}
}

sf::Vector2f Snake::DirToVector(SnakeDirection dir)
{
	using Settings::Unit;

	switch (dir)
	{
	case SnakeDirection::UP:
		return sf::Vector2f(0.f, static_cast<float>(-Unit));
		break;
	case SnakeDirection::DOWN:
		return sf::Vector2f(0.f, static_cast<float>(Unit));
		break;
	case SnakeDirection::LEFT:
		return sf::Vector2f(static_cast<float>(-Unit), 0.f);
		break;
	case SnakeDirection::RIGHT:
		return sf::Vector2f(static_cast<float>(Unit), 0.f);
		break;
	default:
		return sf::Vector2f(static_cast<float>(Unit), 0.f);
		break;
	}
}
