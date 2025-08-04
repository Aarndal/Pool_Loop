#include "PlayerCharacter.h"

void PlayerCharacter::init(const olc::vf2d& startPosition)
{
	m_jumpStartPosition = startPosition;
	m_currentPosition = { startPosition.x + START_POSITION_OFFSET, startPosition.y };
	m_currentVelocity = { 0.0f, 0.0f };
	m_currentRotationAngle = 0.0f;
	m_isFalling = false;
	m_waitingTime = 3.0f;

	m_isInitialized = true;
}

float PlayerCharacter::getCurrentAirResistance(InputHandler::Movement movement)
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

bool PlayerCharacter::jump()
{
	if (m_currentState == State::IDLE)
	{
		olc::vf2d jumpStartPosition = m_currentPosition;

		m_jumpEndPosition =
		{
			jumpStartPosition.x + 500.0f,
			jumpStartPosition.y - 150.0f,
		};

		m_jumpDirection = (m_jumpEndPosition - jumpStartPosition).norm();

		m_currentState = State::JUMP;

		increaseCurrentRotationAngle(acosf(m_jumpDirection.dot(olc::vf2d{ 0.0f, -1.0f })));

		return true;
	}

	return false;
}

olc::vf2d PlayerCharacter::moveHorizontal(float elapsedTime, InputHandler::Movement moveDirection)
{
	switch (m_currentState)
	{
	case State::START:
	{
		m_currentVelocity.x = 0.0f;
		m_waitingTime -= elapsedTime;

		if (m_waitingTime <= 0.0f)
		{
			m_currentState = State::WALK;
		}

		break;
	}
	case State::WALK:
	{
		m_currentVelocity.x = m_spData->getLinearSpeed();
		//TODO: wiggle();
		break;
	}
	case State::FALL:
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
		default:
			m_currentVelocity.x = 0.0f;
			break;
		}
		break;
	}
	case State::END:
		m_currentVelocity.x = 0.0f;
		break;
	default:
		break;
	}

	m_currentPosition.x += m_currentVelocity.x * elapsedTime;

	if (m_currentState == State::WALK && m_currentPosition.x >= m_jumpStartPosition.x)
	{
		m_currentState = State::IDLE;
		m_currentVelocity.x = 0.0f;
		m_currentPosition = m_jumpStartPosition;
	}

	return m_currentPosition;
}

olc::vf2d PlayerCharacter::moveVertical(float elapsedTime, float gravity)
{
	switch (m_currentState)
	{
	case State::JUMP:
	{
		//increaseCurrentRotationAngle(acosf(m_jumpDirection.dot(olc::vf2d{ 0.0f, 1.0f })));

		m_currentVelocity = m_jumpDirection * 500.0f;
		m_currentPosition += m_currentVelocity * elapsedTime;

		float currentJumpHeight = m_jumpEndPosition.y - m_currentPosition.y;

		if (currentJumpHeight >= 0.0f)
		{
			m_currentState = State::FALL;
			m_isRotating = true;
			m_currentVelocity = { 0.0f, 0.0f };
		}
		break;
	}
	case State::FALL:
	{
		m_currentVelocity.y += 0.5f * gravity * elapsedTime;

		m_currentVelocity.y = std::min(m_currentVelocity.y, m_spData->getMaxFallSpeed());

		m_currentVelocity.y /= getCurrentAirResistance(InputHandler::Movement::NONE);

		m_currentPosition.y += m_currentVelocity.y * elapsedTime;
		break;
	}
	default:
		m_currentVelocity.y = 0.0f;
		break;
	}

	if (m_currentPosition.y > 1100)
	{
		m_currentState = PlayerCharacter::State::END;
	}

	return m_currentPosition;
}

float PlayerCharacter::rotate(const float elapsedTime)
{
	if (m_inputHandler.isKeyHeld(olc::Key::SPACE))
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

	return m_currentRotationAngle;
}

bool PlayerCharacter::draw(const Camera& camera)
{
	int currentImageIndex{ 0 };

	if (m_currentState == State::FALL)
	{
		if (m_isRotating)
			currentImageIndex = 1; // Use the rotated image
	}

	if (m_spData->getImages()[currentImageIndex].Decal())
	{
		m_pEngine->DrawPartialRotatedDecal(
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
