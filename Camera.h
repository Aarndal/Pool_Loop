#pragma once
#include <olcPixelGameEngine.h>

class Camera
{
public:
	Camera(olc::vf2d startPos) :m_offset{ startPos }, yMin{ startPos.y } {}
	void move(olc::vf2d offset) 
	{
		m_offset += offset;
		m_offset.y = m_offset.y > yMax ? yMax : m_offset.y;
		m_offset.y = m_offset.y < yMin ? yMin : m_offset.y;
	}
	olc::vf2d transform(olc::vf2d pos) const
	{
		return pos - m_offset;
	}

private:
	olc::vf2d m_offset;
	float yMax{0.f};
	float yMin{};
};

