#include "GameOverMenu.h"

#include "Scene.h"
#include "GamePlay.h"

GameOverMenu::GameOverMenu(std::shared_ptr<Context> context) :
	m_context(context)
{
}

GameOverMenu::GameOverMenu(std::shared_ptr<Context> context, int playerScore) :
	m_context(context),
	m_playerScore(playerScore)
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
				tryChangeScene();
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
	initTitle();
	initButtons();
	initScoreInfo();
	initSounds();

	m_gameOverSound.play();
}

void GameOverMenu::draw()
{
	m_context->m_window->clear();

	m_context->m_window->draw(m_title);
	m_context->m_window->draw(*m_playerScoreText);
	m_context->m_window->draw(m_playAgainButton);
	m_context->m_window->draw(m_exitButton);

	m_context->m_window->display();
}

void GameOverMenu::tryChangeScene()
{
	if (m_isPlayAgainButtonActive)
		m_context->m_sceneManager->push(std::make_unique<GamePlay>(m_context), true);
	else if (m_isExitButtonActive)
		m_context->m_window->close();
}

void GameOverMenu::initTitle()
{
	auto& font = m_context->m_assetManager->getFont(FontType::PRIMARYFONT);

	// Title text
	m_title.setFont(font);
	m_title.setCharacterSize(Settings::SNAKE_TITLE_SIZE);
	m_title.setString("Game Over");
	m_title.setFillColor(sf::Color::White);

	// Set origin on the middle
	m_title.setOrigin(m_title.getGlobalBounds().width / 2,
		m_title.getGlobalBounds().height / 2);
	// Center horizontally
	m_title.setPosition(Settings::W_WIDTH / 2, 50.f);

	// =================================================
}

void GameOverMenu::initButtons()
{
	auto& font = m_context->m_assetManager->getFont(FontType::PRIMARYFONT);

	// Play again button text
	m_playAgainButton.setFont(font);
	m_playAgainButton.setString("Play again");
	m_playAgainButton.setCharacterSize(Settings::BUTTON_TEXT_SIZE);
	m_playAgainButton.setFillColor(sf::Color::White);

	// Set origin on the middle
	m_playAgainButton.setOrigin(m_playAgainButton.getGlobalBounds().width / 2,
		m_playAgainButton.getGlobalBounds().height / 2);
	// Center horizontally
	m_playAgainButton.setPosition(Settings::W_WIDTH / 2, 175.f);

	// =================================================

	// Exit button
	m_exitButton.setFont(font);
	m_exitButton.setString("Exit");
	m_exitButton.setCharacterSize(Settings::BUTTON_TEXT_SIZE);
	m_exitButton.setFillColor(sf::Color::White);

	// Set origin on the middle
	m_exitButton.setOrigin(m_exitButton.getGlobalBounds().width / 2,
		m_exitButton.getGlobalBounds().height / 2);
	// Center horizontally
	m_exitButton.setPosition(Settings::W_WIDTH / 2, 230.f);

	// =================================================
}

void GameOverMenu::initScoreInfo()
{
	auto& font = m_context->m_assetManager->getFont(FontType::PRIMARYFONT);
	// Player score text
	m_playerScoreText = std::make_unique<sfe::RichText>(font);
	m_playerScoreText->setCharacterSize(25);
	*m_playerScoreText << sf::Color::White << "Your score: "
		<< sf::Color::Yellow << std::to_string(m_playerScore);

	// Set origin on the middle
	m_playerScoreText->setOrigin(m_playerScoreText->getGlobalBounds().width / 2,
		m_playerScoreText->getGlobalBounds().height / 2);
	// Center horizontally
	m_playerScoreText->setPosition(Settings::W_WIDTH / 2, 115.f);

	// =================================================
}

void GameOverMenu::initSounds()
{
	m_gameOverSound.setBuffer(m_context->m_assetManager->getSound(SoundType::GAMEOVER));
}
