#pragma once
#include <olcPixelGameEngine.h>

class Camera
{
public:
	Camera(olc::vf2d startPos) :m_offset{ startPos } {}
	void move(olc::vf2d offset) 
	{
		m_offset += offset;
	}
	olc::vf2d transform(olc::vf2d pos) const
	{
		return pos - m_offset;
	}

private:
	olc::vf2d m_offset;
};

