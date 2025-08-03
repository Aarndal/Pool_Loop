#pragma once

#include <numbers>
#include <olcPixelGameEngine.h>
#include "PlayerData.h"
#include "Animation.h"
#include "Score.h"
class Camera;

class PlayerCharacter
{
public:
	PlayerCharacter(std::shared_ptr<PlayerData> data) : m_data{ std::move(data) }
	{
		m_currentAngularSpeed = m_data->getAngularSpeed();
	}

	enum struct State
	{
		START,
		WALK,
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

	// Initialization methods
	void init(const olc::vf2d& startPosition);

	// Getters and Setters
	bool getIsFalling() const { return m_isFalling; }
	bool getIsRotating() const { return m_isRotating; }
	olc::vf2d getPosition() const { return m_currentPosition; }
	State getCurrentState() const { return m_currentState; }

	float getCurrentRotationAngle() const { return m_currentRotationAngle; }
	float getCurrentRotationAngleDegrees() const { return m_currentRotationAngle * 180.0f / static_cast<float>(std::numbers::pi); }

	float getCurrentAirResistance(Movement movement);

	// Movement methods
	bool jump();
	olc::vf2d moveHorizontal(float elapsedTime, Movement moveDirection);
	olc::vf2d moveVertical(float elapsedTime, float gravity);
	float rotate(float elapsedTime, olc::PixelGameEngine& engine);

	bool draw(olc::PixelGameEngine& engine, const Camera& camera);

private:
	std::shared_ptr<PlayerData> m_data;
	Animation m_animator{ {
			"resources\\PC_Cat_00_Stretched.png",
			"resources\\PC_Cat_00_Round.png"
		}, 1.0f };

	State m_currentState{ State::START };

	bool m_isInitialized{ false };
	bool m_isFalling{ false };
	bool m_isRotating{ false };

	float m_currentRotationAngle{ 0.0f };
	float m_currentAngularSpeed{ 0.0f };
	float m_angularBoost{ 1.0f };

	olc::vf2d m_currentVelocity{ 0.0f, 0.0f };
	olc::vf2d m_currentPosition{ 0.0f, 0.0f };
	olc::vf2d m_jumpDirection{ 0.0f, 0.0f };
	olc::vf2d m_jumpEndPosition{ 0.0f, 0.0f };


	bool increaseCurrentRotationAngle(float deltaAngle)
	{
		if (std::fabs(deltaAngle) > static_cast<float>(2.0 * std::numbers::pi)) // Don't allow rotation angles greater than 360 degrees
			return false;

		m_currentRotationAngle += deltaAngle;

		if (m_currentRotationAngle >= static_cast<float>(2.0 * std::numbers::pi))
		{
			m_currentRotationAngle -= static_cast<float>(2.0 * std::numbers::pi);
			Score::getInstance().addRotation();
		}
		if (m_currentRotationAngle < 0.0f)
		{
			m_currentRotationAngle += static_cast<float>(2.0 * std::numbers::pi);
			Score::getInstance().addRotation();
		}
		return true;
	}

	bool increaseCurrentRotationAngleDegrees(float deltaAngleDegrees)
	{
		if (std::fabs(deltaAngleDegrees) > 360.0f) // Don't allow rotation angles greater than 360 degrees
			return false;

		float deltaAngle = deltaAngleDegrees * static_cast<float>(std::numbers::pi) / 180.0f;

		return increaseCurrentRotationAngle(deltaAngle);
	}

	bool increaseAngularSpeed(float angularBoost)
	{
		if (angularBoost <= 0.0f)
			return false;

		m_currentAngularSpeed += angularBoost;
		return true;
	}

	bool increaseAngularBoost(float deltaAngularBoost)
	{
		if (deltaAngularBoost <= 0.0f)
			return false;

		m_angularBoost += deltaAngularBoost;
		return true;
	}
};