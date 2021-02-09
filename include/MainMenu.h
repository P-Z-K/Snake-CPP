#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "Scene.h"
#include "GamePlay.h"
#include "Game.h"

class MainMenu : public Scene
{
private:
	std::shared_ptr<Context> m_context;
	sf::Event m_event;

	// Texts
	sf::Text m_title;
	sf::Text m_playButton;
	sf::Text m_exitButton;

	// Menu logic
	bool m_isPlayButtonFocused;
	bool m_isExitButtonFocused;

public:
	MainMenu(const std::shared_ptr<Context>& context);

public:
	void handleInputs() override;
	void update(const sf::Time& deltaTime) override;
	void init() override;
	void draw() override;

private:
	void tryChangeScene();

	void initTitle();
	void initButtons();

};

