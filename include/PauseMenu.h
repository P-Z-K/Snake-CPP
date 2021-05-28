#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Scene.h"


class PauseMenu : public Scene
{
private:
	std::shared_ptr<Context> m_context;
	sf::Event m_event{};

	// Texts
	sf::Text m_pauseText{};

public:
	PauseMenu() = delete;
	PauseMenu(std::shared_ptr<Context> context);

	void HandleInputs() override;
	void Update(const sf::Time& deltaTime) override;
	void Init() override;
	void Draw() override;
};

