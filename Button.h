#pragma once
#include <limits>
#include <olcPixelGameEngine.h>

struct BoundingBox2D
{
	olc::vf2d min{ std::numeric_limits<float>::max(),std::numeric_limits<float>::max()};
	olc::vf2d max{ -std::numeric_limits<float>::max() ,-std::numeric_limits<float>::max()};
};

inline bool isInside(const BoundingBox2D& bb, olc::vf2d point)
{
	return point.x < bb.max.x
		&& point.x > bb.min.x
		&& point.y < bb.max.y
		&& point.y > bb.min.y;
}



class Button
{
public:
	Button(BoundingBox2D bb, std::function<void()> action)
		: 
		m_bb{ bb }
		, m_action{ std::move(action) }
	{
	}

	bool hit(olc::vf2d point)const;
	void invoke() const;
	void draw(olc::PixelGameEngine* pge) const;

private:
	BoundingBox2D m_bb;
	std::function<void()> m_action;
	//olc::Renderable m_image;
};


