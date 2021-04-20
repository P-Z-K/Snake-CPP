#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <RichText.hpp>

#include <memory>

#include "Game.h"

class GameOverMenu : public Scene
{
private:
	std::shared_ptr<Context> m_context;
	sf::Event m_event;

	sf::Sound m_gameOverSound;

	// Texts
	sf::Text m_title;
	sf::Text m_playAgainButton;
	sf::Text m_exitButton;
	std::unique_ptr<sfe::RichText> m_playerScoreText;

	// Player
	int m_playerScore = -1;

	// Menu logic
	bool m_isPlayAgainButtonActive = true;
	bool m_isExitButtonActive = false;

public:
	GameOverMenu(const std::shared_ptr<Context>& context);
	GameOverMenu(const std::shared_ptr<Context>& context, int playerScore);

public:
	void handleInputs() override;
	void update(const sf::Time& deltaTime) override;
	void init() override;
	void draw() override;

private:
	void tryChangeScene();

	void initTitle();
	void initButtons();
	void initScoreInfo();
	void initSounds();

};

