#include "GameOverMenu.h"

GameOverMenu::GameOverMenu(const std::shared_ptr<Context>& context) :
	m_context(context),
	m_isPlayAgainButtonActive(true),
	m_isExitButtonActive(false),
	m_event()
{
}

void GameOverMenu::handleInputs()
{
	while (m_context->m_window->pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			m_context->m_window->close();
		else if (m_event.type == sf::Event::KeyPressed)
		{
			if (m_event.key.code == sf::Keyboard::Up || m_event.key.code == sf::Keyboard::Down)
			{
				m_isPlayAgainButtonActive = !m_isPlayAgainButtonActive;
				m_isExitButtonActive = !m_isExitButtonActive;
			}
			else if (m_event.key.code == sf::Keyboard::Enter)
			{
				sceneChanger();
			}
		}

	}
}

void GameOverMenu::update(const sf::Time& deltaTime)
{
	if (m_isPlayAgainButtonActive)
	{
		m_playAgainButton.setFillColor(sf::Color::Yellow);
		m_exitButton.setFillColor(sf::Color::White);
	}
	else
	{
		m_exitButton.setFillColor(sf::Color::Yellow);
		m_playAgainButton.setFillColor(sf::Color::White);
	}
}

void GameOverMenu::init()
{
	auto& font = m_context->m_assetManager->getFont(FontType::PRIMARYFONT);

	// Title text
	m_title.setFont(font);
	m_title.setCharacterSize(Settings::SNAKE_TITLE_SIZE);
	m_title.setString("Game Over");
	m_title.setFillColor(sf::Color::White);

	// Set origin on the middle
	m_title.setOrigin(m_title.getGlobalBounds().width / 2, m_title.getGlobalBounds().height / 2);
	// Center horizontally
	m_title.setPosition(Settings::W_WIDTH / 2, 50.f);

	// =================================================

	// Play again button text
	m_playAgainButton.setFont(font);
	m_playAgainButton.setString("Play again");
	m_playAgainButton.setCharacterSize(Settings::BUTTON_TEXT_SIZE);
	m_playAgainButton.setFillColor(sf::Color::White);

	// Set origin on the middle
	m_playAgainButton.setOrigin(m_playAgainButton.getGlobalBounds().width / 2, 
								m_playAgainButton.getGlobalBounds().height / 2);
	// Center horizontally
	m_playAgainButton.setPosition(Settings::W_WIDTH / 2, 165.f);

	// =================================================

	// Exit button
	m_exitButton.setFont(font);
	m_exitButton.setString("Exit");
	m_exitButton.setCharacterSize(Settings::BUTTON_TEXT_SIZE);
	m_exitButton.setFillColor(sf::Color::White);

	// Set origin on the middle
	m_exitButton.setOrigin(m_exitButton.getGlobalBounds().width / 2, m_exitButton.getGlobalBounds().height / 2);
	// Center horizontally
	m_exitButton.setPosition(Settings::W_WIDTH / 2, 220.f);

	// =================================================
}

void GameOverMenu::draw()
{
	m_context->m_window->clear();

	m_context->m_window->draw(m_title);
	m_context->m_window->draw(m_playAgainButton);
	m_context->m_window->draw(m_exitButton);

	m_context->m_window->display();
}

void GameOverMenu::sceneChanger()
{
	if (m_isPlayAgainButtonActive)
		m_context->m_sceneManager->push(std::make_unique<GamePlay>(m_context), true);
	else if (m_isExitButtonActive)
		m_context->m_window->close();
}
