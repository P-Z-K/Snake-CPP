#pragma once

struct Position
{
	const int x;
	const int y;
};

namespace Settings
{
	inline constexpr size_t W_LENGTH = 480;
	inline constexpr size_t W_WIDTH = 640;
	inline constexpr int UNIT = 16;
	inline constexpr size_t SNAKE_START_LENGTH = 3;
	inline constexpr Position SNAKE_START_POS { 6, 6 };
	inline constexpr float SNAKE_SPEED = 0.15f;

	inline constexpr size_t SNAKE_TITLE_SIZE = 45;
	inline constexpr size_t BUTTON_TEXT_SIZE = 25;
	inline constexpr size_t PAUSE_TITLE_SIZE = 30;

	// Make sure that screen will properly displays every unit, no unit cutting by screen
	static_assert(W_LENGTH % UNIT == 0 && W_LENGTH % UNIT == 0);
}
