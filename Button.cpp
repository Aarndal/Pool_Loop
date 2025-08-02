#include "Button.h"

bool Button::hit(olc::vf2d point) const
{
	return isInside(m_bb, point);
}

void Button::invoke() const
{
	std::invoke(m_action);
}

void Button::draw(olc::PixelGameEngine* pge) const
{
	if (!pge) return;

	/*if (m_image.Decal())
		pge->DrawDecal(m_bb.min, m_image.Decal());*/

#ifdef _DEBUG
	pge->DrawRectDecal(m_bb.min, m_bb.max - m_bb.min, olc::RED);
#endif

}
