#pragma once

struct Position
{
	const int m_x;
	const int m_y;
};

namespace Settings
{
	inline constexpr unsigned int W_Length = 352;
	inline constexpr unsigned int W_Width = 480;
	inline constexpr int Unit = 16;
	inline constexpr unsigned int Snake_Start_Length = 3;
	inline constexpr Position Snake_Start_Pos { 6, 6 };
	inline constexpr float Snake_Speed = 0.12f;
	inline constexpr float Snake_Speed_Increase = 0.001f;

	inline constexpr unsigned int Snake_Title_Size = 45;
	inline constexpr unsigned int Button_Text_Size = 25;
	inline constexpr unsigned int Pause_Title_Size = 30;

	// Make sure that screen will properly displays every unit, no unit cutting by screen
	static_assert(W_Width % Unit == 0 && W_Length % Unit == 0);
}
