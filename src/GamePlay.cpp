#include "GamePlay.h"

GamePlay::GamePlay(const std::shared_ptr<Context>& context) :
	m_context(context),
	m_snakeDir(SnakeDirection::RIGHT),
	m_snakeSpeed(Settings::SNAKE_SPEED),
	m_event(),
	m_gen(m_rd()),
	m_playerScore(0)
{

}

void GamePlay::handleInputs()
{
	while (m_context->m_window->pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			m_context->m_window->close();
		else if (m_event.type == sf::Event::KeyPressed)
		{
			if (m_event.key.code == sf::Keyboard::Escape)
				m_context->m_window->close();
			else if (m_event.key.code == sf::Keyboard::Space)
				m_context->m_sceneManager->push(std::make_unique<PauseMenu>(m_context));

			snakeMovementHandler(m_event.key.code);
		}
	}
}

void GamePlay::update(const sf::Time& deltaTime)
{
	elapsedTime += deltaTime;

	// Its a snake speed limiter
	while (elapsedTime.asSeconds() > m_snakeSpeed)
	{
		// Check walls collisions
		for (auto& wall : m_walls)
		{
			if (m_snake.isOn(wall))
			{
				std::cout << "Snake hits wall!\n";
				m_context->m_sceneManager->push(std::make_unique<GameOverMenu>(m_context, m_playerScore), true);
			}
		}

		if (m_snake.isSelfIntersects())
		{
			std::cout << "Snake is self intersecting!\n";
			m_context->m_sceneManager->push(std::make_unique<GameOverMenu>(m_context, m_playerScore), true);
		}

		if (m_snake.isOn(m_currentFruit))
		{
			std::cout << "Snake ate fruit!\n";
			++m_playerScore;
			m_snake.grow();

			// Snake ate fruit, thus we spawn another
			spawnFruit();
		}

		// Update texts
		m_scoreText.setString(std::to_string(m_playerScore));

		m_snake.move(m_snakeDir);

		elapsedTime = sf::Time::Zero;
	}
}

void GamePlay::init()
{
	m_context->m_assetManager->loadTexture("Assets/grass.png", TextureType::GRASS, true);
	m_context->m_assetManager->loadTexture("Assets/wall.png", TextureType::WALL, true);

	m_context->m_assetManager->loadTexture("Assets/tail.png", TextureType::SNAKETAIL);
	m_context->m_assetManager->loadTexture("Assets/head.png", TextureType::SNAKEHEAD);


	m_context->m_assetManager->loadTexture("Assets/Fruits/apple.png", TextureType::APPLE);
	m_context->m_assetManager->loadTexture("Assets/Fruits/cherry.png", TextureType::CHERRY);
	m_context->m_assetManager->loadTexture("Assets/Fruits/watermelon.png", TextureType::WATERMELON);
	m_context->m_assetManager->loadTexture("Assets/Fruits/kiwi.png", TextureType::KIWI);


	m_grass.setTexture(m_context->m_assetManager->getTexture(TextureType::GRASS), true);
	// Make grass texture to fill whole screen
	m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

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
	m_walls[2].setPosition(0, (float)screenSizes.height - wallSizes.y);

	// Right wall
	m_walls[3].setTextureRect(sf::IntRect(0, 0, wallSizes.x, screenSizes.height));
	m_walls[3].setPosition((float)screenSizes.width - wallSizes.x, 0);

	m_snake.init(m_context->m_assetManager->getTexture(TextureType::SNAKEHEAD), m_context->m_assetManager->getTexture(TextureType::SNAKETAIL));

	// Handle fruits
	m_fruits[0].setTexture(m_context->m_assetManager->getTexture(TextureType::APPLE));
	m_fruits[1].setTexture(m_context->m_assetManager->getTexture(TextureType::CHERRY));
	m_fruits[2].setTexture(m_context->m_assetManager->getTexture(TextureType::WATERMELON));
	m_fruits[3].setTexture(m_context->m_assetManager->getTexture(TextureType::KIWI));
	spawnFruit();

	auto& font = m_context->m_assetManager->getFont(FontType::PRIMARYFONT);

	// Score text
	m_scoreText.setFont(font);
	m_scoreText.setString(std::to_string(m_playerScore));
	m_scoreText.setFillColor(sf::Color::Yellow);
}

void GamePlay::draw()
{
	m_context->m_window->clear();

	m_context->m_window->draw(m_grass);

	for (auto& wall : m_walls)
	{
		m_context->m_window->draw(wall);
	}

	m_context->m_window->draw(m_currentFruit);

	m_context->m_window->draw(m_snake);

	m_context->m_window->draw(m_scoreText);

	m_context->m_window->display();
}

void GamePlay::snakeMovementHandler(sf::Keyboard::Key key)
{
	SnakeDirection newDir;
	switch (key)
	{
	default:
		newDir = m_snakeDir;
		break;
	case sf::Keyboard::Up:
		newDir = SnakeDirection::UP;
		break;
	case sf::Keyboard::Down:
		newDir = SnakeDirection::DOWN;
		break;
	case sf::Keyboard::Left:
		newDir = SnakeDirection::LEFT;
		break;
	case sf::Keyboard::Right:
		newDir = SnakeDirection::RIGHT;
		break;
	}

	// TODO: it could be better implemented
	// Prevent snake from doing illegal moves
	if (newDir == SnakeDirection::UP && m_snakeDir == SnakeDirection::DOWN ||
		newDir == SnakeDirection::DOWN && m_snakeDir == SnakeDirection::UP ||
		newDir == SnakeDirection::LEFT && m_snakeDir == SnakeDirection::RIGHT ||
		newDir == SnakeDirection::RIGHT && m_snakeDir == SnakeDirection::LEFT
		)
		return;

	m_snakeDir = newDir;
}

void GamePlay::spawnFruit()
{
	using Settings::UNIT;

	// Divide windows dimensions to get units per one dimension
	static int unitsInWidth = Settings::W_WIDTH / (int)UNIT;
	static int unitsInLength = Settings::W_LENGTH / (int)UNIT;

	// In the first and the last grid's cell we placed walls, 
	// thus we dont want to spawn apple into walls
	static std::uniform_int_distribution<> xPos(1, unitsInWidth - 2);
	static std::uniform_int_distribution<> yPos(1, unitsInLength - 2);

	std::uniform_int_distribution<> fruitIndex(0, m_fruits.size() - 1);

	m_currentFruit = m_fruits[fruitIndex(m_gen)];

	// Place fruit exactly into the grid cell
	m_currentFruit.setPosition((float)xPos(m_gen) * UNIT, (float)yPos(m_gen) * UNIT);

	// Check if spawned fruit collides with snake body, if so, try to spawn at diffrent position
	for (const auto& piece : m_snake.getBody())
	{
		if (m_currentFruit.getGlobalBounds().intersects(piece.getGlobalBounds()))
		{
			std::cout << "Fruit spawned at snake!\n";
			spawnFruit();
		}
	}
}
