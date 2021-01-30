#include "GamePlay.h"

GamePlay::GamePlay(const std::shared_ptr<Context>& context) :
	m_context(context)
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::handleInputs()
{
	sf::Event e;

	while (m_context->m_window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			m_context->m_window->close();
		else if (e.type == sf::Event::KeyPressed)
		{

		}
	}
}

void GamePlay::update(const sf::Time& deltaTime)
{
}

void GamePlay::init()
{
	m_context->m_assetManager->loadTexture("Assets/tail.png", TextureType::SNAKETAIL);
	m_context->m_assetManager->loadTexture("Assets/head.png", TextureType::SNAKEHEAD);
	m_context->m_assetManager->loadTexture("Assets/grass.png", TextureType::GRASS, true);

	m_snakeHead.setTexture(m_context->m_assetManager->getTexture(TextureType::SNAKEHEAD));
	m_grass.setTexture(m_context->m_assetManager->getTexture(TextureType::GRASS), true);

	m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

	std::cout << m_grass.getTextureRect().height << ';' << m_grass.getTextureRect().width;

	for (auto& tail : m_tail)
	{
		tail.setTexture(m_context->m_assetManager->getTexture(TextureType::SNAKETAIL));
	}

	//m_snakeTail.setTexture(m_context->m_assetManager->getTexture(TextureType::SNAKETAIL));

	// Only for testing purposes
	m_snakeHead.setPosition(150.f, 150.f);

	sf::Vector2f start(150.f, 150.f);
	for (auto& tail : m_tail)
	{
		start -= sf::Vector2f(16.f, 0);
		sf::Vector2f newPos = start;
		tail.setPosition(newPos);
	}
	//m_snakeTail.setPosition(134.f, 150.f);
}

void GamePlay::draw()
{
	m_context->m_window->clear();

	m_context->m_window->draw(m_grass);

	m_context->m_window->draw(m_snakeHead);

	for (auto& tail : m_tail)
	{
		m_context->m_window->draw(tail);
	}

	//m_context->m_window->draw(m_snakeTail);

	m_context->m_window->display();
}
