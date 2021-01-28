#pragma once

#include <memory>

#include <SFML\System\Time.hpp>

#include "Scene.h"
#include "Game.h"

class MainMenu : public Scene
{
private:
	std::shared_ptr<Context> m_context;

	sf::Text m_title;
	sf::Text m_playButton;
	sf::Text m_exitButton;

	bool m_isPlayButtonFocused;
	bool m_isExitButtonFocused;

public:
	MainMenu(std::shared_ptr<Context>& context);
	~MainMenu();

public:
	void handleInputs() override;
	void update(const sf::Time& deltaTime) override;
	void init() override;
	void draw() override;

};

