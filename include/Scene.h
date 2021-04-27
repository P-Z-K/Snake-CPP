#pragma once

#include <SFML\System\Time.hpp>

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void HandleInputs() = 0;
	virtual void Update(const sf::Time& deltaTime) = 0;
	virtual void Init() = 0;
	virtual void Draw() = 0;
};

