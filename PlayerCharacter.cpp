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
		m_jumpStartPosition = m_currentPosition;
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
		m_currentVelocity.x = -m_data.getLinearSpeed();
		break;
	case Movement::RIGHT:
		m_currentVelocity.x = m_data.getLinearSpeed();
		break;
	default:
		m_currentVelocity.x = 0.0f;
		break;
	}

	m_currentPosition.x += m_currentVelocity.x / m_data.getAirResistance() * elapsedTime;

	return m_currentPosition;
}

olc::vf2d PlayerCharacter::moveVertical(float elapsedTime, float gravity)
{
	if (m_currentState == State::FALL)
	{
		m_currentVelocity.y += gravity * elapsedTime;

		if (m_currentVelocity.y > m_data.getMaxFallSpeed())
			m_currentVelocity.y = m_data.getMaxFallSpeed();

		m_currentPosition.y += 0.5f * m_currentVelocity.y / m_data.getAirResistance() * elapsedTime;
	}
	else if (m_currentState == State::JUMP)
	{
		olc::vf2d jumpPosition{ m_jumpStartPosition.x + 10.0f , m_jumpStartPosition.y - 10.0f };

		olc::vf2d jumpDirection = jumpPosition - m_jumpStartPosition;

		m_currentVelocity = jumpDirection * 5.0f;

		m_currentPosition += m_currentVelocity * elapsedTime;

		float jumpHeight = m_currentPosition.y - jumpPosition.y;

		if (jumpHeight <= 0.0f)
			m_currentState = State::FALL;
	}
	else
	{
		m_currentVelocity.y = 0.0f;
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
		m_currentRotationAngle += m_data.getAngularSpeed() * elapsedTime;

		if (m_currentRotationAngle <= 360.0f)
			m_currentRotationAngle -= 360.0f;
	}

	return m_currentRotationAngle;
}

bool PlayerCharacter::draw(olc::PixelGameEngine& engine, const Camera& camera)
{
	if (m_currentState == State::FALL)
	{
		int currentImageIndex{ 0 };

		if (m_isRotating)
			currentImageIndex = 1; // Use the rotated image

		engine.DrawPartialRotatedDecal(camera.transform(m_currentPosition), m_data.getImages()[currentImageIndex].Decal(), m_currentRotationAngle, { 0.5f * (float)m_data.getImages()[currentImageIndex].Sprite()->width,  0.5f * (float)m_data.getImages()[currentImageIndex].Sprite()->height }, {}, m_data.getImages()[currentImageIndex].Sprite()->Size());

		return true;
	}

	engine.DrawDecal(camera.transform(m_currentPosition), m_data.getImages()[0].Decal());

	return true;
}
