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
	m_context->m_assetManager->loadTexture("Assets/wall.png", TextureType::WALL, true);

	m_snakeHead.setTexture(m_context->m_assetManager->getTexture(TextureType::SNAKEHEAD));
	m_grass.setTexture(m_context->m_assetManager->getTexture(TextureType::GRASS), true);

	for (auto& wall : m_walls)
	{
		wall.setTexture(m_context->m_assetManager->getTexture(TextureType::WALL));
	}

	sf::IntRect screenSizes(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));
	sf::Vector2u wallSizes(m_context->m_assetManager->getTexture(TextureType::WALL).getSize());

	// Top wall
	m_walls[0].setTextureRect(sf::IntRect(0, 0, screenSizes.width, wallSizes.y));

	// Left wall
	m_walls[1].setTextureRect(sf::IntRect(0, 0, wallSizes.x, screenSizes.height));

	// Bottom wall
	m_walls[2].setTextureRect(sf::IntRect(0, 0, screenSizes.width, wallSizes.y));
	m_walls[2].setPosition(0, screenSizes.height - wallSizes.y);

	// Right wall
	m_walls[3].setTextureRect(sf::IntRect(0, 0, wallSizes.x, screenSizes.height));
	m_walls[3].setPosition(screenSizes.width - wallSizes.x, 0);


	m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));


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

	for (auto& wall : m_walls)
	{
		m_context->m_window->draw(wall);
	}


	m_context->m_window->draw(m_snakeHead);

	for (auto& tail : m_tail)
	{
		m_context->m_window->draw(tail);
	}

	m_context->m_window->display();
}
