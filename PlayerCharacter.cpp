#include "PlayerCharacter.h"
#include "Camera.h"
#include "GameSceneBackground.h"

void PlayerCharacter::init(const olc::vf2d& startPosition) //TODO: Add EndPosition
{
	m_currentPosition = startPosition;
	m_currentVelocity = { 0.0f, 0.0f };
	m_currentRotationAngle = 0.0f;
	m_isFalling = false;

	m_isInitialized = true;
}

float PlayerCharacter::getCurrentAirResistance(Movement movement)
{
	float currentAirResistance{ 0.5f };

	if (!m_isRotating)
	{
		float lerpFactor{ std::fabs(std::cosf(getCurrentRotationAngle())) };

		if (movement == Movement::NONE)
			lerpFactor = 1 - lerpFactor;

		currentAirResistance = std::lerp(m_data->getAirResistance(), 1.0f, lerpFactor);
	}

	return currentAirResistance;
}

bool PlayerCharacter::jump()
{
	if (m_currentState == State::START || m_currentState == State::IDLE)
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

olc::vf2d PlayerCharacter::moveHorizontal(float elapsedTime, PlayerCharacter::Movement moveDirection)
{
	switch (moveDirection)
	{
	case Movement::LEFT:
		m_currentVelocity.x = -m_data->getLinearSpeed() / getCurrentAirResistance(moveDirection);
		break;
	case Movement::RIGHT:
		m_currentVelocity.x = m_data->getLinearSpeed() / getCurrentAirResistance(moveDirection);
		break;
	default:
		m_currentVelocity.x = 0.0f;
		break;
	}

	m_currentPosition.x += m_currentVelocity.x * elapsedTime;

	return m_currentPosition;
}

olc::vf2d PlayerCharacter::moveVertical(float elapsedTime, float gravity)
{
	switch (m_currentState)
	{
	case PlayerCharacter::State::JUMP:
	{
		/*increaseCurrentRotationAngle(acosf(m_jumpDirection.dot(olc::vf2d{ 0.0f, 1.0f })));*/

		m_currentVelocity = m_jumpDirection * 300.0f;
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
	case PlayerCharacter::State::FALL:
	{
		m_currentVelocity.y += 0.5f * gravity * elapsedTime;

		if (m_currentVelocity.y > m_data->getMaxFallSpeed())
			m_currentVelocity.y = m_data->getMaxFallSpeed();

		m_currentVelocity.y /= getCurrentAirResistance(Movement::NONE);

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

float PlayerCharacter::rotate(float elapsedTime, olc::PixelGameEngine& engine)
{
	if (engine.GetKey(olc::Key::SPACE).bPressed)
	{
		m_isRotating = !m_isRotating;
	}

	if (m_isRotating)
	{
		increaseCurrentRotationAngleDegrees(m_data->getAngularSpeed() * elapsedTime);
	}

	return m_currentRotationAngle;
}

bool PlayerCharacter::draw(olc::PixelGameEngine& engine, const Camera& camera)
{
	int currentImageIndex{ 0 };

	if (m_currentState == State::FALL)
	{
		if (m_isRotating)
			currentImageIndex = 1; // Use the rotated image
	}
	if (m_data->getImages()[currentImageIndex].Decal())
	{
		engine.DrawPartialRotatedDecal(camera.transform(m_currentPosition), m_data->getImages()[currentImageIndex].Decal(), getCurrentRotationAngle(), { 0.5f * (float)m_data->getImages()[currentImageIndex].Sprite()->width,  0.5f * (float)m_data->getImages()[currentImageIndex].Sprite()->height }, {}, m_data->getImages()[currentImageIndex].Sprite()->Size());
	}
	return true;
}
