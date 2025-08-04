#include "InputHandler.h"

bool InputHandler::isJumpPressed() const
{
	return m_pEngine->GetKey(olc::Key::SPACE).bPressed;
}

InputHandler::Movement InputHandler::getMovement() const
{
	if (isKeyHeld(olc::Key::LEFT) || isKeyHeld(olc::Key::A))
		return Movement::LEFT;

	if (isKeyHeld(olc::Key::RIGHT) || isKeyHeld(olc::Key::D))
		return Movement::RIGHT;

	return Movement::NONE;
}
