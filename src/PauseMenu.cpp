#include "PauseMenu.h"

#include "Scene.h"
#include "Game.h"

PauseMenu::PauseMenu(std::shared_ptr<Context> context) :
	m_context(context)
{
}

void PauseMenu::handleInputs()
{
	while (m_context->m_window->pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			m_context->m_window->close();
		else if (m_event.type == sf::Event::KeyPressed)
		{
			if (m_event.key.code == sf::Keyboard::Space)
				m_context->m_sceneManager->pop();
		}
	}
}

void PauseMenu::update(const sf::Time& deltaTime)
{
}

void PauseMenu::init()
{
	auto& font = m_context->m_assetManager->getFont(FontType::PRIMARYFONT);

	// Pause title
	m_pauseText.setFont(font);
	m_pauseText.setString("Paused");
	m_pauseText.setCharacterSize(Settings::PAUSE_TITLE_SIZE);
	m_pauseText.setFillColor(sf::Color::White);
	m_pauseText.setLetterSpacing(1.5f);

	// Set origin on the middle
	m_pauseText.setOrigin(m_pauseText.getGlobalBounds().width / 2, m_pauseText.getGlobalBounds().height / 2);

	// Center horizontally
	m_pauseText.setPosition(Settings::W_WIDTH / 2, 150.f);
}

void PauseMenu::draw()
{
	// we dont use clear method there, as we dont want to clear screen with our gameplay
	m_context->m_window->draw(m_pauseText);
	m_context->m_window->display();
}
