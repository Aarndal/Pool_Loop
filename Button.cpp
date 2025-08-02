#include "Button.h"



bool Button::hit(olc::vf2d point) const
{
	return isInside(m_bb, point);
}

void Button::invoke() const
{
	std::invoke(m_action);
}

namespace
{
	template<typename ... Ts>
	struct Visiter : Ts ... {
		using Ts::operator() ...;
	};
}

void Button::loadImage()
{
	std::visit(
		Visiter{ 
			[&](const std::filesystem::path& path)
			{
				olc::Renderable image;
				image.Load(path.string());
				m_image = std::move(image);
			},
			[&](const olc::Renderable&) {} },
		m_image
	);
}

void Button::draw(olc::PixelGameEngine* pge, DrawingState state) const
{
	if (!pge) return;

	std::visit(
		Visiter{ 
			[](const std::filesystem::path&) {},
			[&](const olc::Renderable& image) 
		{
			switch (state)
			{
			case DrawingState::highlight: pge->DrawDecal(m_bb.min - 0.05f * size(m_bb), image.Decal(), {1.1f,1.1f}, olc::RED); break;
			case DrawingState::pressed: pge->DrawDecal(m_bb.min+ 0.05f * size(m_bb), image.Decal(), {0.9f,0.9f}); break;
			case DrawingState::none: pge->DrawDecal(m_bb.min, image.Decal()); break;
			}
		} 
		},
		m_image
	);
		

#ifdef _DEBUG
	pge->DrawRectDecal(m_bb.min, m_bb.max - m_bb.min, olc::RED);
#endif

}
