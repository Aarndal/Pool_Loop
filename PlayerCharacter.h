#pragma once

#include <olcPixelGameEngine.h>
#include "PlayerData.h"
#include "Animation.h"

class PlayerCharacter
{
public:
	PlayerCharacter(PlayerData&& data) : m_data{ std::move(data) }
	{
	}

	enum struct State
	{
		START,
		MOVE,
		IDLE,
		JUMP,
		FALL,
		END
	};

	enum struct Movement
	{
		NONE,
		LEFT,
		RIGHT,
	};

	// Getters and Setters
	bool getIsFalling() const { return m_isFalling; }
	olc::vf2d getPosition() const { return m_currentPosition; }

	// Initialization methods
	void init(const olc::vf2d& startPosition);

	// Movement methods
	bool jump(const olc::PixelGameEngine& engine);
	olc::vf2d moveHorizontal(float elapsedTime, Movement moveDirection);
	olc::vf2d moveVertical(float elapsedTime, float gravity);
	float rotate(float elapsedTime, olc::PixelGameEngine& engine);

	bool draw(olc::PixelGameEngine& engine);

private:
	PlayerData m_data;
	Animation m_animator{ {
			"resources\\PC_Cat_00_Stretched.png",
			"resources\\PC_Cat_00_Round.png"
		}, 1.0f };

	State m_currentState{ State::START };

	bool m_isInitialized{ false };
	bool m_isFalling{ false };
	bool m_isRotating{ false };
	
	float m_currentRotationAngle{ 0.0f};

	olc::vf2d m_currentVelocity{ 0.0f, 0.0f };
	olc::vf2d m_currentPosition{ 0.0f, 0.0f };
};

