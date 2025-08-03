#pragma once
#include <limits>
#include <variant>
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

inline auto size(const BoundingBox2D& bb)
{
	return bb.max - bb.min;
}

class Button
{
public:
	Button(BoundingBox2D bb, std::filesystem::path path, std::function<void()> action)
		: m_bb{ bb }
		, m_action{ std::move(action) }
		, m_image{ path }
	{
	}

	void loadImage();

	void update(olc::PixelGameEngine* pge);

	enum class DrawingState
	{
		highlight,
		pressed,
		none
	};

private:
	bool hit(olc::vf2d point)const;
	void invoke() const;
	void draw(olc::PixelGameEngine* pge, DrawingState state = DrawingState::none) const;
	bool m_bPressed{ false };

	BoundingBox2D m_bb;
	std::function<void()> m_action;
	std::variant< std::filesystem::path, olc::Renderable> m_image;

};


