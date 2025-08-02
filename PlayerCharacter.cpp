#include "PlayerCharacter.h"

olc::vf2d PlayerCharacter::move(float elapsedTime, PlayerCharacter::Movement moveDirection)
{
	switch (moveDirection)
	{
	case Movement::LEFT:
		m_velocity.x = -m_data->getLinearSpeed();
		break;
	case Movement::RIGHT:
		m_velocity.x = m_data->getLinearSpeed();
		break;
	default:
		m_velocity.x = 0.0f;
		break;
	}
	m_position += m_velocity * elapsedTime;
	return m_position;
}
