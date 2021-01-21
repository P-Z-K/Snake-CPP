#pragma once

#include <SFML\System\Time.hpp>

class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};

	virtual void handleInputs() = 0;
	virtual void update(sf::Time deltaTime) = 0;
	virtual void init() = 0;

	virtual void start() {};
	virtual void pause() {};
};

