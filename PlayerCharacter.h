#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include <numbers>
#include <olcPixelGameEngine.h>
#include "PlayerData.h"
#include "InputHandler.h"
#include "Animation.h"
#include "Score.h"

class GameScene;
class Camera;

constexpr float START_POSITION_OFFSET{ -650.0f };

class PlayerCharacter
{
public:
	// Constructors
	PlayerCharacter(std::shared_ptr<PlayerData> data, InputHandler inputHandler, const olc::vf2d& startPosition);

	// Enums
	enum struct State : uint8_t
	{
		START = 0,
		WALK = 1,
		IDLE = 2,
		JUMP = 3,
		FALL = 4,
		END = 5,
	};

	// Getters and Setters
	[[nodiscard]] bool getIsRotating() const { return m_isRotating; }
	[[nodiscard]] olc::vf2d getPosition() const { return m_currentPosition; }
	[[nodiscard]] State getCurrentState() const { return m_currentState; }

	[[nodiscard]] float getCurrentRotationAngle() const { return m_currentRotationAngle; }
	[[nodiscard]] float getCurrentRotationAngleDegrees() const { return m_currentRotationAngle * 180.0f / static_cast<float>(std::numbers::pi); }
	[[nodiscard]] float getCurrentAirResistance(const InputHandler::Movement movement) const;

	// Update method
	void update(const float elapsedTime, const GameScene& currentScene);

	// Movement methods
	void wait(const float elapsedTime);
	void jump();
	void moveHorizontal(const float elapsedTime, const InputHandler::Movement moveDirection);
	void moveVertical(const float elapsedTime, const float gravity);
	void rotate(const float elapsedTime);

	// Animation methods
	bool draw(olc::PixelGameEngine& refEngine, const Camera& camera) const;

private:
	// Members
	std::shared_ptr<PlayerData> m_spData;

	InputHandler m_inputHandler;
	Animation m_animator{ {
			"resources/PC_Cat_00_Stretched.png",
			"resources/PC_Cat_00_Round.png"
		}, 1.0f };

	State m_currentState{ State::START };

	bool m_isRotating{ false };

	float m_waitingTime{ 3.0f };
	float m_currentRotationAngle{ 0.0f };
	float m_currentAngularSpeed{ 0.0f };
	float m_angularBoost{ 1.0f };

	olc::vf2d m_currentVelocity{ 0.0f, 0.0f };
	olc::vf2d m_currentPosition{ 0.0f, 0.0f };
	olc::vf2d m_jumpDirection{ 0.0f, 0.0f };
	olc::vf2d m_jumpStartPosition{ 0.0f, 0.0f };
	olc::vf2d m_jumpEndPosition{ 0.0f, 0.0f };

	// Methods
	bool increaseCurrentRotationAngle(const float deltaAngle);
	bool increaseCurrentRotationAngleDegrees(const float deltaAngleDegrees);
	bool increaseAngularSpeed(const float angularBoost);
	bool increaseAngularBoost(const float deltaAngularBoost);
};

#endif // PLAYER_CHARACTER_H