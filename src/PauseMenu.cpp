#include "PauseMenu.h"

PauseMenu::PauseMenu(const std::shared_ptr<Context>& context) :
	m_context(context),
	m_event()
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

	m_pauseText.setFont(font);
	m_pauseText.setString("Paused");
	m_pauseText.setCharacterSize(Settings::PAUSE_TITLE_SIZE);
	m_pauseText.setFillColor(sf::Color::Black);

	// Set origin on the middle
	m_pauseText.setOrigin(m_pauseText.getGlobalBounds().width / 2, m_pauseText.getGlobalBounds().height / 2);

	// Center horizontally
	m_pauseText.setPosition(Settings::W_WIDTH / 2, 150.f);
}

void PauseMenu::draw()
{
	m_context->m_window->draw(m_pauseText);
	m_context->m_window->display();
}
