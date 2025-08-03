#include "PlayerData.h"
#include "Animation.h"

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
