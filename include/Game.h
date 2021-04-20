#pragma once

#include "SFML/Graphics.hpp"

#include <memory>

#include "AssetManager.h"
#include "SceneManager.h"
#include "Settings.h"


struct Context
{
	std::unique_ptr<AssetManager> m_assetManager;
	std::unique_ptr<SceneManager> m_sceneManager;
	std::unique_ptr<sf::RenderWindow> m_window;

	Context()
	{
		m_assetManager = std::make_unique<AssetManager>();
		m_sceneManager = std::make_unique<SceneManager>();
		m_window       = std::make_unique<sf::RenderWindow>();
	}
};


class Game
{
private:
	std::shared_ptr<Context> m_context;

public:
	Game();

public:
	void run();
};

