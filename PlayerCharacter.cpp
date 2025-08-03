#include "PlayerCharacter.h"
#include "Camera.h"
#include "GameSceneBackground.h"

// Initialization methods
void PlayerCharacter::init(const olc::vf2d& startPosition) //TODO: Add jumpPosition
{
	m_currentPosition = startPosition;
	m_currentVelocity = { 0.0f, 0.0f };
	m_currentRotationAngle = 0.0f;
	m_isFalling = false;

	m_isInitialized = true;
}

bool PlayerCharacter::jump(float elapsedTime, const olc::PixelGameEngine& engine)
{
	if (m_currentState == State::START || m_currentState == State::IDLE)
	{
		olc::vf2d jumpStartPosition = m_currentPosition;

		m_jumpEndPosition =
		{
			jumpStartPosition.x + 100.0f,
			jumpStartPosition.y - 100.0f,
		};

		m_jumpDirection = (m_jumpEndPosition - jumpStartPosition).norm();

		m_currentState = State::JUMP;
		return true;
	}

	return false;
}

olc::vf2d PlayerCharacter::moveHorizontal(float elapsedTime, PlayerCharacter::Movement moveDirection)
{
	switch (moveDirection)
	{
	case Movement::LEFT:
		m_currentVelocity.x = -m_data->getLinearSpeed();
		break;
	case Movement::RIGHT:
		m_currentVelocity.x = m_data->getLinearSpeed();
		break;
	default:
		m_currentVelocity.x = 0.0f;
		break;
	}

	m_currentVelocity /= m_data->getAirResistance();

	m_currentPosition.x += m_currentVelocity.x * elapsedTime;

	return m_currentPosition;
}

olc::vf2d PlayerCharacter::moveVertical(float elapsedTime, float gravity)
{
	switch (m_currentState)
	{
	case PlayerCharacter::State::JUMP:
	{
		m_currentRotationAngle = acosf(m_jumpDirection.dot(olc::vf2d{ 1.0f, 0.0f }));

		m_currentVelocity = m_jumpDirection * 100.0f;
		m_currentPosition += m_currentVelocity * elapsedTime;

		float currentJumpHeight = m_jumpEndPosition.y - m_currentPosition.y;

		if (currentJumpHeight >= 0.0f)
		{
			m_currentState = State::FALL;
			m_isRotating = true;
		}
		break;
	}
	case PlayerCharacter::State::FALL:
	{
		m_currentVelocity.y -= gravity * elapsedTime / m_data->getAirResistance();

		if (m_currentVelocity.y > m_data->getMaxFallSpeed())
			m_currentVelocity.y = m_data->getMaxFallSpeed();

		m_currentPosition.y += 0.5f * m_currentVelocity.y * elapsedTime;
		break;
	}
	default:
		m_currentVelocity.y = 0.0f;
		break;
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
		m_currentRotationAngle += m_data->getAngularSpeed() * elapsedTime;

		if (m_currentRotationAngle >= 360.0f) // Reset rotation angle if it exceeds 360 degrees
			m_currentRotationAngle -= 360.0f;
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

	engine.DrawPartialRotatedDecal(camera.transform(m_currentPosition), m_data->getImages()[currentImageIndex].Decal(), m_currentRotationAngle, { 0.5f * (float)m_data->getImages()[currentImageIndex].Sprite()->width,  0.5f * (float)m_data->getImages()[currentImageIndex].Sprite()->height }, {}, m_data->getImages()[currentImageIndex].Sprite()->Size());

	return true;
}
