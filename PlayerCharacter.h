#pragma once

#include "olcPixelGameEngine.h"
#include "PlayerData.h"

class PlayerCharacter
{
public:
	PlayerCharacter(PlayerData* data) : m_data{ data }
	{
	}

	enum struct State
	{
		START,
		IDLE,
		JUMP,
		MOVE,
		FALL,
	};

	enum struct Movement
	{
		NONE,
		LEFT,
		RIGHT,
	};

public:
	olc::vf2d move(float elapsedTime, Movement moveDirection);

private:
	PlayerData* m_data{};

	olc::vf2d m_position{ 0.0f, 0.0f };
	olc::vf2d m_velocity{ 0.0f, 0.0f };
};

