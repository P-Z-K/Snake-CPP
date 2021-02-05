#pragma once

#include <SFML/Graphics.hpp>

struct GridStartPos
{
	int x, y;
};

namespace Settings
{
	inline constexpr size_t W_LENGTH = 480;
	inline constexpr size_t W_WIDTH = 640;
	inline constexpr int UNIT = 16;
	inline constexpr size_t SNAKE_START_LENGTH = 3;
	inline constexpr GridStartPos SNAKE_START_POS { 6, 6 };
	inline constexpr float SNAKE_SPEED = 0.15f;
}
