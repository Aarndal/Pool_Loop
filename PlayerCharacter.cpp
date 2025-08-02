#include "PlayerCharacter.h"

// Initialization methods
inline void PlayerCharacter::init(const olc::vf2d& startPosition)
{
	m_currentPosition = startPosition;
	m_currentVelocity = { 0.0f, 0.0f };
	m_currentRotationAngle = 0.0f;
	m_isFalling = false;
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

float PlayerCharacter::rotate(float elapsedTime, const olc::PixelGameEngine& engine)
{
	if (engine.GetKey(olc::Key::SPACE).bPressed)
	{

	}

	return 0.0f;
}
