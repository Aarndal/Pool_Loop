#include "Animation.h"


olc::Renderable loadImage(const std::filesystem::path& path)
{
	olc::Renderable renderable;
	renderable.Load(path.string());
	return renderable;
}

std::vector<olc::Renderable> loadImages(const std::vector<std::filesystem::path>& vecImagePaths)
{
	std::vector<olc::Renderable> renderables;
	std::ranges::transform(vecImagePaths, std::back_inserter(renderables), loadImage);
	return renderables;
}


Animation::Animation(const std::vector<std::filesystem::path>& vecImagePaths, float frameTime) 
	: m_vecImages{ loadImages(vecImagePaths) }
	, m_frameTime{ frameTime }
{
}

void Animation::draw(olc::vf2d pos, float fElepsedTime, olc::PixelGameEngine* pge)
{
	m_currentImageIndex = updateIndex(m_currentImageIndex, fElepsedTime);

	pge->DrawRotatedDecal(pos, m_vecImages[m_currentImageIndex].Decal(), 0.f);
}

int Animation::updateIndex(int currentIndex, float fElepsedTime)
{
	m_time += fElepsedTime;
	if (m_time >= m_frameTime)
	{
		const int newIndex = ++currentIndex;
		return newIndex == m_vecImages.size() ? 0 : newIndex;
	}
	return currentIndex;
}
