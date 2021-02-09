#pragma once

#include <SFML/Graphics.hpp>
#include <RichText.hpp>

#include <memory>


#include "Scene.h"
#include "Game.h"
#include "GamePlay.h"

class GameOverMenu : public Scene
{
private:
	std::shared_ptr<Context> m_context;
	sf::Event m_event;

	// Texts
	sf::Text m_title;
	sf::Text m_playAgainButton;
	sf::Text m_exitButton;
	std::unique_ptr<sfe::RichText> m_playerScoreText;

	// Player
	int m_playerScore;

	// Menu logic
	bool m_isPlayAgainButtonActive;
	bool m_isExitButtonActive;

public:
	GameOverMenu(const std::shared_ptr<Context>& context);
	GameOverMenu(const std::shared_ptr<Context>& context, int playerScore);

public:
	void handleInputs() override;
	void update(const sf::Time& deltaTime) override;
	void init() override;
	void draw() override;

private:
	void sceneChanger();

};

