#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <olcPixelGameEngine.h>

class InputHandler
{
public:
	// Constructors
	InputHandler() = delete; // Prevent default constructor

	InputHandler(olc::PixelGameEngine* pEngine)
	{
		m_pEngine = pEngine;
	};

	// Enums
	enum struct Movement : int8_t
	{
		NONE = 0,
		LEFT = -1,
		RIGHT = 1,
	};

	[[nodiscard]] bool isKeyPressed(const olc::Key key) const { return m_pEngine->GetKey(key).bPressed; }
	[[nodiscard]] bool isKeyHeld(const olc::Key key) const { return m_pEngine->GetKey(key).bHeld; }
	[[nodiscard]] bool isKeyReleased(const olc::Key key) const { return m_pEngine->GetKey(key).bReleased; }

	[[nodiscard]] bool isJumpPressed() const;

	[[nodiscard]] Movement getMovement() const;

private:
	olc::PixelGameEngine* m_pEngine;
};

#endif // INPUT_HANDLER_H