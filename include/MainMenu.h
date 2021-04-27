#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "Game.h"
#include "Scene.h"

class MainMenu : public Scene
{
private:
	std::shared_ptr<Context> m_context;
	sf::Event m_event{};

	// Texts
	sf::Text m_title{};
	sf::Text m_playButton{};
	sf::Text m_exitButton{};

	// Menu logic
	bool m_isPlayButtonFocused = true;
	bool m_isExitButtonFocused = false;

public:
	MainMenu() = delete;
	MainMenu(std::shared_ptr<Context> context);

	void HandleInputs() override;
	void Update(const sf::Time& deltaTime) override;
	void Init() override;
	void Draw() override;

private:
	void TryChangeScene();

	void InitTitle();
	void InitButtons();

};

