#pragma once

#include <memory>
#include <array>

#include "Scene.h"
#include "Game.h"
#include "Snake.h"

class GamePlay : public Scene
{
private:
	sf::Time elapsedTime;
	sf::Event m_event;
	std::shared_ptr<Context> m_context;

	std::array<sf::Sprite, 4> m_walls;
	sf::Sprite m_grass;
	sf::Sprite m_apple;

	const float m_snakeSpeed;
	SnakeDirection m_snakeDir;
	Snake m_snake;

	// Random numbers
	std::random_device m_rd;
	std::mt19937 m_gen;

public:
	GamePlay(const std::shared_ptr<Context>& context);
	~GamePlay();

public:
	void handleInputs() override;
	void update(const sf::Time& deltaTime) override;
	void init() override;
	void draw() override;

private:
	void snakeMovementHandler(sf::Keyboard::Key key);
	void spawnApple();

};

