#include "PlayerCharacter.h"

#include "GameScene.h"
#include "SceneManager.h"

PlayerCharacter::PlayerCharacter(std::shared_ptr<PlayerData> data, InputHandler inputHandler, const olc::vf2d& startPosition) :
	m_spData{ std::move(data) },
	m_inputHandler{ std::move(inputHandler) },
	m_currentPosition { startPosition.x + START_POSITION_OFFSET, startPosition.y },
	m_jumpStartPosition{ startPosition },
	m_currentAngularSpeed{ m_spData->getAngularSpeed() }
{

}

float PlayerCharacter::getCurrentAirResistance(const InputHandler::Movement movement) const
{
	float currentAirResistance{ 0.15f };

	if (!m_isRotating)
	{
		float lerpFactor{ std::fabs(std::cosf(getCurrentRotationAngle())) };

		if (movement == InputHandler::Movement::NONE)
			lerpFactor = 1 - lerpFactor;

		currentAirResistance = std::lerp(m_spData->getAirResistance(), 1.0f, lerpFactor);
	}

	return currentAirResistance;
}

void PlayerCharacter::update(const float elapsedTime, const GameScene& currentScene)
{
	const float gravity = currentScene.getGravity();

	switch (this->getCurrentState())
	{
	case State::START:
	{
		this->wait(elapsedTime);
		break;
	}
	case State::WALK:
	{
		this->moveHorizontal(elapsedTime, InputHandler::Movement::RIGHT);
		break;
	}
	case State::IDLE:
		if (m_inputHandler.isJumpPressed())
			this->jump();
		break;
	case State::JUMP:
	{
		this->moveVertical(elapsedTime, gravity);
		break;
	}
	case State::FALL:
	{
		this->rotate(elapsedTime);

		this->moveVertical(elapsedTime, gravity);

		const InputHandler::Movement currentMoveDirection = m_inputHandler.getMovement();

		this->moveHorizontal(elapsedTime, currentMoveDirection);
		break;
	}
	case State::END:
	{
		constexpr float targetPosX = 1920 - 1600 + 0.5 * 1600;

		Score::getInstance().finaliseScore(
			this->getCurrentRotationAngle(),
			this->getIsRotating(),
			std::abs(this->getPosition().x - targetPosX));
		SceneManager::getInstance().changeScene(SceneManager::Scene::gameOver);
		break;
	}
	}
}

void PlayerCharacter::wait(const float elapsedTime)
{
	m_currentVelocity.x = 0.0f;
	m_waitingTime -= elapsedTime;

	if (m_waitingTime <= 0.0f)
	{
		m_currentState = State::WALK;
	}
}

void PlayerCharacter::jump()
{
	const olc::vf2d jumpStartPosition = m_currentPosition;

	m_jumpEndPosition =
	{
		jumpStartPosition.x + 500.0f,
		jumpStartPosition.y - 150.0f,
	};

	m_jumpDirection = (m_jumpEndPosition - jumpStartPosition).norm();

	increaseCurrentRotationAngle(acosf(m_jumpDirection.dot(olc::vf2d{ 0.0f, -1.0f })));

	m_currentState = State::JUMP;
}

void PlayerCharacter::moveHorizontal(const float elapsedTime, const InputHandler::Movement moveDirection)
{
	if (m_currentState == State::WALK)
	{
		m_currentVelocity.x = m_spData->getLinearSpeed();
		//TODO: wiggle();
	}
	else if (m_currentState == State::FALL)
	{
		switch (moveDirection)
		{
		case InputHandler::Movement::LEFT:
			m_currentVelocity.x = -m_spData->getLinearSpeed() / getCurrentAirResistance(moveDirection);
			break;
		case InputHandler::Movement::RIGHT:
			m_currentVelocity.x = m_spData->getLinearSpeed() / getCurrentAirResistance(moveDirection);
			break;
		case InputHandler::Movement::NONE:
			m_currentVelocity.x = 0.0f;
			break;
		}
	}
	else
	{
		m_currentVelocity.x = 0.0f;
	}

	m_currentPosition.x += m_currentVelocity.x * elapsedTime;

	if (m_currentState == State::WALK && m_currentPosition.x >= m_jumpStartPosition.x)
	{
		m_currentState = State::IDLE;
		m_currentVelocity.x = 0.0f;
		m_currentPosition = m_jumpStartPosition;
	}
}

void PlayerCharacter::moveVertical(const float elapsedTime, const float gravity)
{
	if (m_currentState == State::JUMP)
	{
		m_currentVelocity = m_jumpDirection * 500.0f;
		m_currentPosition += m_currentVelocity * elapsedTime;

		const float currentJumpHeight = m_jumpEndPosition.y - m_currentPosition.y;

		if (currentJumpHeight >= 0.0f)
		{
			m_currentState = State::FALL;
			m_isRotating = true;
			m_currentVelocity = { 0.0f, 0.0f };
		}
	}
	else if (m_currentState == State::FALL)
	{
		m_currentVelocity.y += 0.5f * gravity * elapsedTime;

		m_currentVelocity.y = std::min(m_currentVelocity.y, m_spData->getMaxFallSpeed());

		m_currentVelocity.y /= getCurrentAirResistance(InputHandler::Movement::NONE);

		m_currentPosition.y += m_currentVelocity.y * elapsedTime;
	}
	else
	{
		m_currentVelocity.y = 0.0f;
	}

	if (m_currentPosition.y > 1100)
	{
		m_currentState = State::END;
	}
}

void PlayerCharacter::rotate(const float elapsedTime)
{
	if (m_inputHandler.isKeyPressed(olc::Key::SPACE))
	{
		m_isRotating = !m_isRotating;
	}

	if (m_isRotating)
	{
		increaseCurrentRotationAngleDegrees(m_currentAngularSpeed * elapsedTime);

		if (increaseAngularBoost(0.5f * elapsedTime))
			increaseAngularSpeed(m_angularBoost);
	}

	if (!m_isRotating)
	{
		m_currentAngularSpeed = m_spData->getAngularSpeed();
		m_angularBoost = 0.0f;
	}
}

bool PlayerCharacter::draw(olc::PixelGameEngine& refEngine, const Camera& camera) const
{
	int currentImageIndex{ 0 };

	if (m_currentState == State::FALL)
	{
		if (m_isRotating)
			currentImageIndex = 1; // Use the rotated image
	}

	if (m_spData->getImages()[currentImageIndex].Decal())
	{
		refEngine.DrawPartialRotatedDecal(
			camera.transform(m_currentPosition),
			m_spData->getImages()[currentImageIndex].Decal(),
			getCurrentRotationAngle(),
			{
					0.5f * static_cast<float>(m_spData->getImages()[currentImageIndex].Sprite()->width),
					0.5f * static_cast<float>(m_spData->getImages()[currentImageIndex].Sprite()->height) },
			{},
			m_spData->getImages()[currentImageIndex].Sprite()->Size());
	}

	return true;
}

bool PlayerCharacter::increaseCurrentRotationAngle(const float deltaAngle)
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

bool PlayerCharacter::increaseCurrentRotationAngleDegrees(const float deltaAngleDegrees)
{
	if (std::fabs(deltaAngleDegrees) > 360.0f) // Don't allow rotation angles greater than 360 degrees
		return false;

	const float deltaAngle = deltaAngleDegrees * static_cast<float>(std::numbers::pi) / 180.0f;

	return increaseCurrentRotationAngle(deltaAngle);
}

bool PlayerCharacter::increaseAngularSpeed(const float angularBoost)
{
	if (angularBoost <= 0.0f)
		return false;

	m_currentAngularSpeed += angularBoost;
	return true;
}

bool PlayerCharacter::increaseAngularBoost(const float deltaAngularBoost)
{
	if (deltaAngularBoost <= 0.0f)
		return false;

	m_angularBoost += deltaAngularBoost;
	return true;
}
