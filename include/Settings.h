#pragma once

#include <SFML/Graphics.hpp>

struct GridStartPos
{
	float x, y;
};

namespace Settings
{
	inline constexpr size_t W_LENGTH = 480;
	inline constexpr size_t W_WIDTH = 640;
	inline constexpr float UNIT = 16.f;
	inline constexpr size_t START_SNAKE_LENGTH = 3;
	inline constexpr GridStartPos GRID_START_POS { 6.f, 6.f };
	inline constexpr float SNAKE_SPEED = 0.25f;
}
