#pragma once

#include <SFML/Graphics.hpp>

struct GridStartPos
{
	float x, y;
};

constexpr size_t W_LENGTH = 480;
constexpr size_t W_WIDTH = 640;
constexpr float CELL_SIZE = 16.f;
constexpr size_t START_SNAKE_LENGTH = 3;
constexpr GridStartPos GRID_START_POS { 6.f, 6.f };
constexpr float SNAKE_SPEED = 0.25f;