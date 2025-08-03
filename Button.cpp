#include "Button.h"

namespace
{
	constexpr float  buttonHighlightSize = 5.f; // +5%
	constexpr float  buttonPressedSize = -5.f;  // -5%
}

bool Button::hit(olc::vf2d point) const
{
	return isInside(m_bb, point);
}

void Button::invoke() const
{
	std::invoke(m_action);
}

void Button::update(olc::PixelGameEngine* pge)
{
	if (hit(pge->GetMousePos()))
	{
		if (pge->GetMouse(0).bReleased && m_bPressed)
		{
			if (hit(pge->GetMousePos()))
			{
				invoke();
			}
		}
		const auto mouseState = pge->GetMouse(0);
		if (mouseState.bHeld || mouseState.bPressed)
		{
			draw(pge, Button::DrawingState::pressed);
			m_bPressed = true;
		}
		else
		{
			draw(pge, Button::DrawingState::highlight);
			m_bPressed = false;
		}
	}
	else
	{
		draw(pge);
	}

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
			case DrawingState::highlight: pge->DrawDecal(m_bb.min - 0.5f * buttonHighlightSize / 100.f * size(m_bb), image.Decal(), olc::vf2d{1.f,1.f} + buttonHighlightSize/100.f); break;
			case DrawingState::pressed: pge->DrawDecal(m_bb.min - 0.5f * buttonPressedSize / 100.f * size(m_bb), image.Decal(), olc::vf2d{ 1.f,1.f } + buttonPressedSize / 100.f); break;
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
