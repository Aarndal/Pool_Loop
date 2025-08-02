#pragma once

#include <olcPixelGameEngine.h>
#include "PlayerData.h"

class PlayerCharacter
{
public:
	PlayerCharacter(PlayerData data) : m_data{ data }
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

	// Getters and Setters
	olc::vf2d getPosition() const { return m_currentPosition; }
	void setPosition(const olc::vf2d& position) { m_currentPosition = position; }

	bool getIsFalling() const { return m_isFalling; }
	void setIsFalling(bool isFalling) { m_isFalling = isFalling; }

	// Initialization methods
	void init(const olc::vf2d& startPosition);

	// Movement methods
	olc::vf2d moveHorizontal(float elapsedTime, Movement moveDirection);
	olc::vf2d moveVertical(float elapsedTime, float gravity);
	float rotate(float elapsedTime, const olc::PixelGameEngine& engine);

private:
	PlayerData m_data;

	bool m_isFalling{ false };
	
	float m_currentRotationAngle{ 0.0f};

	olc::vf2d m_currentVelocity{ 0.0f, 0.0f };
	olc::vf2d m_currentPosition{ 0.0f, 0.0f };
};

