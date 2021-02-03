#include "MainMenu.h"

MainMenu::MainMenu(std::shared_ptr<Context>& context) :
	m_context(context),
	m_isPlayButtonFocused(true),
	m_isExitButtonFocused(false)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::handleInputs()
{
	sf::Event e;
	while (m_context->m_window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			m_context->m_window->close();
		else if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Up || e.key.code == sf::Keyboard::Down)
			{
				m_isPlayButtonFocused = !m_isPlayButtonFocused;
				m_isExitButtonFocused = !m_isExitButtonFocused;
			}
			else if (e.key.code == sf::Keyboard::Enter)
			{
				sceneChanger();
			}
		}
	}
}

void MainMenu::update(const sf::Time& deltaTime)
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

void MainMenu::init()
{
	m_context->m_assetManager->loadFont("Assets/PottaOne-Regular.ttf", FontType::PRIMARYFONT);

	auto& font = m_context->m_assetManager->getFont(FontType::PRIMARYFONT);

	// Title
	m_title.setFont(font);
	m_title.setString("Snake");
	m_title.setCharacterSize(45);
	m_title.setFillColor(sf::Color::White);

	// Set origin on the middle
	m_title.setOrigin(m_title.getGlobalBounds().width / 2, m_title.getGlobalBounds().height / 2);
	// Center horizontally
	m_title.setPosition(Settings::W_WIDTH / 2, 50.f);

	// ================================

	// Play button
	m_playButton.setFont(font);
	m_playButton.setString("Play");
	m_playButton.setCharacterSize(25);
	m_playButton.setFillColor(sf::Color::White);

	// Set origin on the middle
	m_playButton.setOrigin(m_playButton.getGlobalBounds().width / 2, m_playButton.getGlobalBounds().height / 2);
	// Center horizontally
	m_playButton.setPosition(Settings::W_WIDTH / 2, 165.f);

	// ================================

	// Exit button
	m_exitButton.setFont(font);
	m_exitButton.setString("Exit");
	m_exitButton.setCharacterSize(25);
	m_exitButton.setFillColor(sf::Color::White);

	// Set origin on the middle
	m_exitButton.setOrigin(m_exitButton.getGlobalBounds().width / 2, m_exitButton.getGlobalBounds().height / 2);
	// Center horizontally
	m_exitButton.setPosition(Settings::W_WIDTH / 2, 220.f);

	// ================================
}

void MainMenu::draw()
{
	m_context->m_window->clear();

	m_context->m_window->draw(m_title);
	m_context->m_window->draw(m_playButton);
	m_context->m_window->draw(m_exitButton);

	m_context->m_window->display();
}

void MainMenu::sceneChanger()
{
	if (m_isExitButtonFocused)
		m_context->m_window->close();

	if (m_isPlayButtonFocused)
		m_context->m_sceneManager->push(std::make_unique<GamePlay>(m_context), true);

}
