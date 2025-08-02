#include "PlayerCharacter.h"
#include "Camera.h"

// Initialization methods
void PlayerCharacter::init(const olc::vf2d& startPosition)
{
	m_currentPosition = startPosition;
	m_currentVelocity = { 0.0f, 0.0f };
	m_currentRotationAngle = 0.0f;
	m_isFalling = false;

	m_isInitialized = true;
}

bool PlayerCharacter::jump(const olc::PixelGameEngine& engine)
{
	if (!m_isFalling && engine.GetKey(olc::Key::SPACE).bPressed)
	{
		m_isFalling = true;
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
	m_currentPosition.x += m_data.getMass() * m_currentVelocity.x * elapsedTime;
	return m_currentPosition;
}

olc::vf2d PlayerCharacter::moveVertical(float elapsedTime, float gravity)
{
	if (m_isFalling)
	{
		m_currentVelocity.y += gravity * elapsedTime;

		if (m_currentVelocity.y > m_data.getMaxFallSpeed())
			m_currentVelocity.y = m_data.getMaxFallSpeed();
	}
	else
	{
		m_currentVelocity.y = 0.0f;
	}
	m_currentPosition.y += 0.5f * m_data.getMass() * m_currentVelocity.y * elapsedTime;
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
		m_currentRotationAngle -= m_data.getAngularSpeed() * elapsedTime;

		if (m_currentRotationAngle <= -360.0f)
			m_currentRotationAngle += 360.0f;
	}

	return m_currentRotationAngle;
}

bool PlayerCharacter::draw(olc::PixelGameEngine& engine, const Camera& camera)
{
	if (m_isFalling)
	{
		if (m_isRotating)
			engine.DrawPartialRotatedDecal(camera.transform(m_currentPosition), m_data.getImages()[1].Decal(), m_currentRotationAngle, { 0.5f*(float)m_data.getImages()[1].Sprite()->width,  0.5f * (float)m_data.getImages()[1].Sprite()->height }, {}, m_data.getImages()[1].Sprite()->Size());
		else
			engine.DrawPartialRotatedDecal(camera.transform(m_currentPosition), m_data.getImages()[0].Decal(), m_currentRotationAngle, { 0.5f * (float)m_data.getImages()[0].Sprite()->width,  0.5f * (float)m_data.getImages()[0].Sprite()->height }, {}, m_data.getImages()[0].Sprite()->Size());

		return true;
	}

	engine.DrawDecal(camera.transform(m_currentPosition), m_data.getImages()[0].Decal());

	return true;
}
