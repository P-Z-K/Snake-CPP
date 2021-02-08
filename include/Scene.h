#pragma once

#include <SFML\System\Time.hpp>



class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};

	virtual void handleInputs() = 0;
	virtual void update(const sf::Time& deltaTime) = 0;
	virtual void init() = 0;
	virtual void draw() = 0;
};

