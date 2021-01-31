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
			if (e.key.code == sf::Keyboard::Escape)
				m_context->m_window->close();
		}
	}
}

void GamePlay::update(const sf::Time& deltaTime)
{

}

void GamePlay::init()
{
	m_context->m_assetManager->loadTexture("Assets/grass.png", TextureType::GRASS, true);
	m_context->m_assetManager->loadTexture("Assets/wall.png", TextureType::WALL, true);
	m_context->m_assetManager->loadTexture("assets/tail.png", TextureType::SNAKETAIL);
	m_context->m_assetManager->loadTexture("assets/head.png", TextureType::SNAKEHEAD);

	m_grass.setTexture(m_context->m_assetManager->getTexture(TextureType::GRASS), true);
	// Make grass texture to fill whole screen
	m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

	for (auto& wall : m_walls)
	{
		wall.setTexture(m_context->m_assetManager->getTexture(TextureType::WALL));
	}

	sf::IntRect screenSizes (m_context->m_window->getViewport(m_context->m_window->getDefaultView()));
	sf::Vector2u wallSizes (m_context->m_assetManager->getTexture(TextureType::WALL).getSize());

	// Top wall
	m_walls[0].setTextureRect(sf::IntRect(0, 0, screenSizes.width, wallSizes.y));

	// Left wall
	m_walls[1].setTextureRect(sf::IntRect(0, 0, wallSizes.x, screenSizes.height));

	// Bottom wall
	m_walls[2].setTextureRect(sf::IntRect(0, 0, screenSizes.width, wallSizes.y));
	m_walls[2].setPosition(0, (float)screenSizes.height - wallSizes.y);

	// Right wall
	m_walls[3].setTextureRect(sf::IntRect(0, 0, wallSizes.x, screenSizes.height));
	m_walls[3].setPosition( (float)screenSizes.width - wallSizes.x, 0);

	m_snake.init(m_context->m_assetManager->getTexture(TextureType::SNAKEHEAD), m_context->m_assetManager->getTexture(TextureType::SNAKETAIL));
}

void GamePlay::draw()
{
	m_context->m_window->clear();

	m_context->m_window->draw(m_grass);

	for (auto& wall : m_walls)
	{
		m_context->m_window->draw(wall);
	}

	m_context->m_window->draw(m_snake);

	m_context->m_window->display();
}
