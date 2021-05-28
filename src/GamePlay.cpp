#include "GamePlay.h"

#include <iostream>

#include "Game.h"
#include "GameOverMenu.h"
#include "PauseMenu.h"
#include "Snake.h"

GamePlay::GamePlay(std::shared_ptr<Context> context) :
	m_context(context),
	m_gen(m_rd())
{
}

void GamePlay::HandleInputs()
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
				m_context->m_sceneManager->Push(std::make_unique<PauseMenu>(m_context));

			HandleSnakeMovement(m_event.key.code);
		}
	}
}

void GamePlay::Update(const sf::Time& deltaTime)
{
	m_elapsedTime += deltaTime;

	// Its a snake speed limiter
	while (m_elapsedTime.asSeconds() > m_snakeSpeed)
	{
		CheckCollisions();

		// Update texts
		m_scoreText.setString(std::to_string(m_playerScore));

		m_snake.Move(m_snakeDir);

		m_elapsedTime = sf::Time::Zero;
	}
}

void GamePlay::Init()
{
	m_context->m_assetManager->LoadTexture("Assets/grass.png", TextureType::GRASS, true);
	m_context->m_assetManager->LoadTexture("Assets/wall.png", TextureType::WALL, true);

	m_context->m_assetManager->LoadTexture("Assets/tail.png", TextureType::SNAKETAIL);
	m_context->m_assetManager->LoadTexture("Assets/head.png", TextureType::SNAKEHEAD);


	m_context->m_assetManager->LoadTexture("Assets/Fruits/apple.png", TextureType::APPLE);
	m_context->m_assetManager->LoadTexture("Assets/Fruits/cherry.png", TextureType::CHERRY);
	m_context->m_assetManager->LoadTexture("Assets/Fruits/watermelon.png", TextureType::WATERMELON);
	m_context->m_assetManager->LoadTexture("Assets/Fruits/kiwi.png", TextureType::KIWI);

	m_context->m_assetManager->LoadSoundBuffer("Assets/Music/Hit.wav", SoundType::HIT);
	m_context->m_assetManager->LoadSoundBuffer("Assets/Music/GameOver.wav", SoundType::GAMEOVER);


	InitTerrain();
	InitSnake();
	InitFruits();
	InitTexts();
	InitSounds();
}

void GamePlay::Draw()
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

void GamePlay::HandleSnakeMovement(sf::Keyboard::Key key)
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

	if (newDir == SnakeDirection::UP && m_snakeDir == SnakeDirection::DOWN ||
		newDir == SnakeDirection::DOWN && m_snakeDir == SnakeDirection::UP ||
		newDir == SnakeDirection::LEFT && m_snakeDir == SnakeDirection::RIGHT ||
		newDir == SnakeDirection::RIGHT && m_snakeDir == SnakeDirection::LEFT
		)
		return;

	m_snakeDir = newDir;
}

void GamePlay::SpawnFruit()
{
	using Settings::Unit;

	// Divide windows dimensions to get units per one dimension
	static int unitsInWidth = Settings::W_Width / Unit;
	static int unitsInLength = Settings::W_Length / Unit;

	// In the first and the last grid's cell we placed walls, 
	// thus we dont want to spawn apple into walls
	static std::uniform_int_distribution<> xPos(1, unitsInWidth - 2);
	static std::uniform_int_distribution<> yPos(1, unitsInLength - 2);

	const std::uniform_int_distribution<> fruitIndex(0, m_fruits.size() - 1);

	m_currentFruit = m_fruits[fruitIndex(m_gen)];

	// Place fruit exactly into the grid cell
	m_currentFruit.setPosition(static_cast<float>(xPos(m_gen)) * Unit, static_cast<float>(yPos(m_gen)) * Unit);

	// Check if spawned fruit collides with snake body, if so, try to spawn at diffrent position
	for (const auto& piece : m_snake.GetBody())
	{
		if (m_currentFruit.getGlobalBounds().intersects(piece.getGlobalBounds()))
		{
			std::cout << "Fruit spawned at snake!\n";
			SpawnFruit();
		}
	}
}

void GamePlay::InitTerrain()
{
	m_grass.setTexture(m_context->m_assetManager->GetTexture(TextureType::GRASS), true);
	// Make grass texture to fill whole screen
	m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

	for (auto& wall : m_walls)
	{
		wall.setTexture(m_context->m_assetManager->GetTexture(TextureType::WALL));
	}

	const sf::IntRect screenSizes(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));
	const sf::Vector2u wallSizes(m_context->m_assetManager->GetTexture(TextureType::WALL).getSize());

	// Top wall
	m_walls[0].setTextureRect(sf::IntRect(0, 0, screenSizes.width, wallSizes.y));

	// Left wall
	m_walls[1].setTextureRect(sf::IntRect(0, 0, wallSizes.x, screenSizes.height));

	// Bottom wall
	m_walls[2].setTextureRect(sf::IntRect(0, 0, screenSizes.width, wallSizes.y));
	m_walls[2].setPosition(0, static_cast<float>(screenSizes.height) - wallSizes.y);

	// Right wall
	m_walls[3].setTextureRect(sf::IntRect(0, 0, wallSizes.x, screenSizes.height));
	m_walls[3].setPosition(static_cast<float>(screenSizes.width) - wallSizes.x, 0);
}

void GamePlay::InitTexts()
{
	auto& font = m_context->m_assetManager->GetFont(FontType::PRIMARYFONT);

	m_scoreText.setFont(font);
	m_scoreText.setString(std::to_string(m_playerScore));
	m_scoreText.setFillColor(sf::Color::Yellow);
}

void GamePlay::InitSnake()
{
	m_snake.Init(m_context->m_assetManager->GetTexture(TextureType::SNAKEHEAD),
		m_context->m_assetManager->GetTexture(TextureType::SNAKETAIL));
}

void GamePlay::InitFruits()
{
	// Handle fruits
	m_fruits[0].setTexture(m_context->m_assetManager->GetTexture(TextureType::APPLE));
	m_fruits[1].setTexture(m_context->m_assetManager->GetTexture(TextureType::CHERRY));
	m_fruits[2].setTexture(m_context->m_assetManager->GetTexture(TextureType::WATERMELON));
	m_fruits[3].setTexture(m_context->m_assetManager->GetTexture(TextureType::KIWI));
	SpawnFruit();
}

void GamePlay::InitSounds()
{
	m_soundtrack = m_context->m_assetManager->GetSoundtrack("Assets/Music/Soundtrack.wav");

	if (m_soundtrack)
	{
		m_soundtrack->setVolume(15.f);
		m_soundtrack->setLoop(true);
		m_soundtrack->play();
	}

	m_hitSound.setBuffer(m_context->m_assetManager->GetSound(SoundType::HIT));
}

void GamePlay::CheckCollisions()
{
	// Check walls collisions
	for (auto& wall : m_walls)
	{
		if (m_snake.IsOn(wall))
		{
			std::cout << "Snake hits wall!\n";
			LoadGameOverMenu();
		}
	}

	if (m_snake.IsSelfIntersects())
	{
		std::cout << "Snake is self intersecting!\n";
		LoadGameOverMenu();
	}

	if (m_snake.IsOn(m_currentFruit))
	{
		HandleSnakeEatFruit();
	}
}

void GamePlay::HandleSnakeEatFruit()
{
	std::cout << "Snake ate fruit!\n";
	++m_playerScore;
	m_hitSound.play();

	m_snake.Grow();

	m_snakeSpeed -= Settings::Snake_Speed_Increase;

	// Snake ate fruit, thus we spawn another
	SpawnFruit();
}

void GamePlay::LoadGameOverMenu()
{
	m_context->m_sceneManager->Push(std::make_unique<GameOverMenu>(m_context, m_playerScore), true);
}
