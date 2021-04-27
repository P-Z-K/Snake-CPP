#include "MainMenu.h"

#include "GamePlay.h"
#include "Game.h"

MainMenu::MainMenu(std::shared_ptr<Context> context) :
	m_context(context)
{
}

void MainMenu::HandleInputs()
{
	while (m_context->m_window->pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			m_context->m_window->close();
		else if (m_event.type == sf::Event::KeyPressed)
		{
			if (m_event.key.code == sf::Keyboard::Up || m_event.key.code == sf::Keyboard::Down)
			{
				m_isPlayButtonFocused = !m_isPlayButtonFocused;
				m_isExitButtonFocused = !m_isExitButtonFocused;
			}
			else if (m_event.key.code == sf::Keyboard::Enter)
			{
				TryChangeScene();
			}
		}
	}
}

void MainMenu::Update(const sf::Time& deltaTime)
{
	if (m_isPlayButtonFocused)
	{
		m_playButton.setFillColor(sf::Color::Yellow);
		m_exitButton.setFillColor(sf::Color::White);
	}
	else
	{
		m_exitButton.setFillColor(sf::Color::Yellow);
		m_playButton.setFillColor(sf::Color::White);
	}
}

void MainMenu::Init()
{
	m_context->m_assetManager->LoadFont("Assets/PottaOne-Regular.ttf", FontType::PRIMARYFONT);

	InitTitle();
	InitButtons();
}

void MainMenu::Draw()
{
	m_context->m_window->clear();

	m_context->m_window->draw(m_title);
	m_context->m_window->draw(m_playButton);
	m_context->m_window->draw(m_exitButton);

	m_context->m_window->display();
}

void MainMenu::TryChangeScene()
{
	if (m_isExitButtonFocused)
		m_context->m_window->close();
	else if (m_isPlayButtonFocused)
		m_context->m_sceneManager->Push(std::make_unique<GamePlay>(m_context), true);
}

void MainMenu::InitTitle()
{
	auto& font = m_context->m_assetManager->GetFont(FontType::PRIMARYFONT);

	// Title
	m_title.setFont(font);
	m_title.setString("Snake");
	m_title.setCharacterSize(Settings::Snake_Title_Size);
	m_title.setFillColor(sf::Color::White);

	// Set origin on the middle
	m_title.setOrigin(m_title.getGlobalBounds().width / 2, m_title.getGlobalBounds().height / 2);
	// Center horizontally
	m_title.setPosition(static_cast<float>(Settings::W_Width) / 2, 50.f);

	// ================================
}

void MainMenu::InitButtons()
{
	auto& font = m_context->m_assetManager->GetFont(FontType::PRIMARYFONT);

	// Play button
	m_playButton.setFont(font);
	m_playButton.setString("Play");
	m_playButton.setCharacterSize(Settings::Button_Text_Size);
	m_playButton.setFillColor(sf::Color::White);

	// Set origin on the middle
	m_playButton.setOrigin(m_playButton.getGlobalBounds().width / 2, m_playButton.getGlobalBounds().height / 2);
	// Center horizontally
	m_playButton.setPosition(static_cast<float>(Settings::W_Width) / 2, 165.f);

	// ================================

	// Exit button
	m_exitButton.setFont(font);
	m_exitButton.setString("Exit");
	m_exitButton.setCharacterSize(Settings::Button_Text_Size);
	m_exitButton.setFillColor(sf::Color::White);

	// Set origin on the middle
	m_exitButton.setOrigin(m_exitButton.getGlobalBounds().width / 2, m_exitButton.getGlobalBounds().height / 2);
	// Center horizontally
	m_exitButton.setPosition(static_cast<float>(Settings::W_Width) / 2, 220.f);

	// ================================
}
