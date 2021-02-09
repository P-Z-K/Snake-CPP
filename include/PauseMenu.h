#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

#include "Scene.h"
#include "Game.h"

class PauseMenu : public Scene
{
private:
	std::shared_ptr<Context> m_context;
	sf::Event m_event;

	// Texts
	sf::Text m_pauseText;

public:
	PauseMenu(const std::shared_ptr<Context>& context);

public:
	void handleInputs() override;
	void update(const sf::Time& deltaTime) override;
	void init() override;
	void draw() override;
};

