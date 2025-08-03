#pragma once
#include <olcPixelGameEngine.h>

class Camera
{
public:
	Camera(olc::vf2d startPos) :m_offset{ startPos } {}
	void move(olc::vf2d offset) 
	{
		m_offset += offset;
		m_offset.y = m_offset.y > 0.f ? 0.f : m_offset.y;
	}
	olc::vf2d transform(olc::vf2d pos) const
	{
		return pos - m_offset;
	}

private:
	olc::vf2d m_offset;
};

