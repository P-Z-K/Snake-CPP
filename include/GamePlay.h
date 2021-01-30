#pragma once

#include <memory>
#include <array>

#include "Scene.h"
#include "Game.h"

class GamePlay : public Scene
{
private:
	std::shared_ptr<Context> m_context;

	// Testing purposes
	std::array<sf::Sprite, 4> m_walls;
	sf::Sprite m_snakeHead;
	sf::Sprite m_grass;
	std::array<sf::Sprite, 5> m_tail;
	//sf::Sprite m_snakeTail;

public:
	GamePlay(const std::shared_ptr<Context>& context);
	~GamePlay();

public:
	void handleInputs() override;
	void update(const sf::Time& deltaTime) override;
	void init() override;
	void draw() override;

};

