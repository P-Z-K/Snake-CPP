#include "Game.h"
#include "MainMenu.h"
#include "Settings.h"

Game::Game() :
	m_context(std::make_shared<Context>())
{
	m_context->m_window->create(sf::VideoMode(Settings::W_Width, Settings::W_Length),
		"Snake",
		sf::Style::Close);

	m_context->m_sceneManager->Push(std::make_unique<MainMenu>(m_context));

	// Testing purposes
	m_context->m_window->setFramerateLimit(250);
}

void Game::Run() const
{
	sf::Clock clock;


	while (m_context->m_window->isOpen())
	{
		sf::Time elapsedTime = clock.getElapsedTime();
		clock.restart();

		m_context->m_sceneManager->ProcessSceneChange();
		m_context->m_sceneManager->GetCurrent()->HandleInputs();
		m_context->m_sceneManager->GetCurrent()->Update(elapsedTime);
		m_context->m_sceneManager->GetCurrent()->Draw();
	}
}
