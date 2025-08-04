#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include <numbers>
#include <olcPixelGameEngine.h>
#include "PlayerData.h"
#include "InputHandler.h"
#include "Animation.h"
#include "Score.h"
#include "Camera.h"

class Camera;

constexpr float START_POSITION_OFFSET{ -650.0f };

class PlayerCharacter
{
public:
	PlayerCharacter(olc::PixelGameEngine* pEngine, std::shared_ptr<PlayerData> data) : m_spData{ std::move(data) }, m_inputHandler{ pEngine }
	{
		m_pEngine = pEngine;
		m_currentAngularSpeed = m_spData->getAngularSpeed();
	}

	enum struct State : uint8_t
	{
		START = 0,
		WALK = 1,
		IDLE = 2,
		JUMP = 3,
		FALL = 4,
		END = 5,
	};

	// Initialisation method
	void init(const olc::vf2d& startPosition);

	// Getters and Setters
	[[nodiscard]] bool getIsFalling() const { return m_isFalling; }
	[[nodiscard]] bool getIsRotating() const { return m_isRotating; }
	[[nodiscard]] olc::vf2d getPosition() const { return m_currentPosition; }
	[[nodiscard]] State getCurrentState() const { return m_currentState; }

	[[nodiscard]] float getCurrentRotationAngle() const { return m_currentRotationAngle; }
	[[nodiscard]] float getCurrentRotationAngleDegrees() const { return m_currentRotationAngle * 180.0f / static_cast<float>(std::numbers::pi); }

	[[nodiscard]] float getCurrentAirResistance(InputHandler::Movement movement);

	// Movement methods
	bool jump();
	olc::vf2d moveHorizontal(float elapsedTime, InputHandler::Movement moveDirection);
	olc::vf2d moveVertical(float elapsedTime, float gravity);
	float rotate(float elapsedTime);

	// Animation methods
	bool draw(const Camera& camera);

private:
	// Members
	olc::PixelGameEngine* m_pEngine{ nullptr };
	std::shared_ptr<PlayerData> m_spData;

	InputHandler m_inputHandler;
	Animation m_animator{ {
			"resources\\PC_Cat_00_Stretched.png",
			"resources\\PC_Cat_00_Round.png"
		}, 1.0f };

	State m_currentState{ State::START };

	bool m_isInitialized{ false };
	bool m_isFalling{ false };
	bool m_isRotating{ false };

	float m_waitingTime{ 0.0f };
	float m_currentRotationAngle{ 0.0f };
	float m_currentAngularSpeed{ 0.0f };
	float m_angularBoost{ 1.0f };

	olc::vf2d m_currentVelocity{ 0.0f, 0.0f };
	olc::vf2d m_currentPosition{ 0.0f, 0.0f };
	olc::vf2d m_jumpDirection{ 0.0f, 0.0f };
	olc::vf2d m_jumpStartPosition{ 0.0f, 0.0f };
	olc::vf2d m_jumpEndPosition{ 0.0f, 0.0f };

	// Methods
	bool increaseCurrentRotationAngle(const float deltaAngle)
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

	bool increaseCurrentRotationAngleDegrees(const float deltaAngleDegrees)
	{
		if (std::fabs(deltaAngleDegrees) > 360.0f) // Don't allow rotation angles greater than 360 degrees
			return false;

		const float deltaAngle = deltaAngleDegrees * static_cast<float>(std::numbers::pi) / 180.0f;

		return increaseCurrentRotationAngle(deltaAngle);
	}

	bool increaseAngularSpeed(const float angularBoost)
	{
		if (angularBoost <= 0.0f)
			return false;

		m_currentAngularSpeed += angularBoost;
		return true;
	}

	bool increaseAngularBoost(const float deltaAngularBoost)
	{
		if (deltaAngularBoost <= 0.0f)
			return false;

		m_angularBoost += deltaAngularBoost;
		return true;
	}
};

#endif // PLAYER_CHARACTER_H