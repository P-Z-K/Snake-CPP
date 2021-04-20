#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <memory>
#include <array>
#include <random>

#include "Game.h"
#include "Scene.h"
#include "Snake.h"


class GamePlay : public Scene
{
private:
	sf::Time elapsedTime{};
	sf::Event m_event{};
	std::shared_ptr<Context> m_context;

	// Music
	std::unique_ptr<sf::Music> m_soundrack{ nullptr };
	sf::Sound m_hitSound{};

	// Texts
	sf::Text m_scoreText{};

	// Terrain
	std::array<sf::Sprite, 4> m_walls;
	sf::Sprite m_grass{};
	std::array<sf::Sprite, 4> m_fruits;
	sf::Sprite m_currentFruit{};

	// Snake
	float m_snakeSpeed = Settings::SNAKE_SPEED;
	SnakeDirection m_snakeDir = SnakeDirection::RIGHT;
	Snake m_snake{};
	int m_playerScore{0};

	// Random numbers
	std::random_device m_rd;
	std::mt19937 m_gen;

public:
	GamePlay(std::shared_ptr<Context> context);

public:
	void handleInputs() override;
	void update(const sf::Time& deltaTime) override;
	void init() override;
	void draw() override;

private:
	void handleSnakeMovement(sf::Keyboard::Key key);
	void spawnFruit();

	void initTerrain();
	void initTexts();
	void initSnake();
	void initFruits();
	void initSounds();

	void checkCollisions();
	void handleSnakeEatFruit();
	void loadGameOverMenu();

};

