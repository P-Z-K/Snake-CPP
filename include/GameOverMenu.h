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
	sf::Event m_event{};

	sf::Sound m_gameOverSound{};

	// Texts
	sf::Text m_title{};
	sf::Text m_playAgainButton{};
	sf::Text m_exitButton{};
	std::unique_ptr<sfe::RichText> m_playerScoreText{ nullptr };

	// Player
	int m_playerScore = -1;

	// Menu logic
	bool m_isPlayAgainButtonActive = true;
	bool m_isExitButtonActive = false;

public:
	GameOverMenu() = delete;
	GameOverMenu(std::shared_ptr<Context> context);
	GameOverMenu(std::shared_ptr<Context> context, int playerScore);

	void HandleInputs() override;
	void Update(const sf::Time& deltaTime) override;
	void Init() override;
	void Draw() override;

private:
	void TryChangeScene();

	void InitTitle();
	void InitButtons();
	void InitScoreInfo();
	void InitSounds();

};

