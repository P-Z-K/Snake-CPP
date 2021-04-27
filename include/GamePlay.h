#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <memory>
#include <array>
#include <random>

#include "Game.h"
#include "Scene.h"
#include "Settings.h"
#include "Snake.h"


class GamePlay : public Scene
{
private:
	sf::Time m_elapsedTime{};
	sf::Event m_event{};
	std::shared_ptr<Context> m_context;

	// Music
	std::unique_ptr<sf::Music> m_soundtrack{ nullptr };
	sf::Sound m_hitSound{};

	// Texts
	sf::Text m_scoreText{};

	// Terrain
	std::array<sf::Sprite, 4> m_walls;
	sf::Sprite m_grass{};
	std::array<sf::Sprite, 4> m_fruits;
	sf::Sprite m_currentFruit{};

	// Snake
	float m_snakeSpeed = Settings::Snake_Speed;
	SnakeDirection m_snakeDir = SnakeDirection::RIGHT;
	Snake m_snake{};
	int m_playerScore{0};

	// Random numbers
	std::random_device m_rd;
	std::mt19937 m_gen;

public:
	GamePlay() = delete;
	GamePlay(std::shared_ptr<Context> context);

	void HandleInputs() override;
	void Update(const sf::Time& deltaTime) override;
	void Init() override;
	void Draw() override;

private:
	void HandleSnakeMovement(sf::Keyboard::Key key);
	void SpawnFruit();

	void InitTerrain();
	void InitTexts();
	void InitSnake();
	void InitFruits();
	void InitSounds();

	void CheckCollisions();
	void HandleSnakeEatFruit();
	void LoadGameOverMenu();

};

