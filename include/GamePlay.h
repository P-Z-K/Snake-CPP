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
	std::shared_ptr<Context> m_context;

	std::array<sf::Sprite, 4> m_walls;
	sf::Sprite m_grass;

	SnakeDirection m_snakeDir;
	Snake m_snake;

public:
	GamePlay(const std::shared_ptr<Context>& context);
	~GamePlay();

public:
	void handleInputs() override;
	void update(const sf::Time& deltaTime) override;
	void init() override;
	void draw() override;

};

