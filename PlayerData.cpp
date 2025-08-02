#include "PlayerData.h"

namespace
{
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
}

bool PlayerData::init(const std::vector<std::filesystem::path>& vecImagePaths)
{
	m_images = loadImages(vecImagePaths);

	if (m_images.empty())
	{
		m_images = loadImages(
			{
				"resources\\PC_Cat_00_Stretched.png",
				"resources\\PC_Cat_00_Round.png"
			});
		return false;
	}

	return true;
}
