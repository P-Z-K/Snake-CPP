#include "Game.h"
#include "MainMenu.h"

Game::Game() :
	m_context(std::make_shared<Context>())
{
	m_context->m_window->create(sf::VideoMode(W_WIDTH, W_LENGTH),
		"Snake",
		sf::Style::Close);
	m_context->m_sceneManager->push(std::make_unique<MainMenu>(m_context));
}

Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;


	while (m_context->m_window->isOpen())
	{
		sf::Time elapsedTime = clock.getElapsedTime();
		clock.restart();

		m_context->m_sceneManager->processSceneChange();
		m_context->m_sceneManager->getCurrent()->draw();
		m_context->m_sceneManager->getCurrent()->handleInputs();
		m_context->m_sceneManager->getCurrent()->update(elapsedTime);
	}
}
