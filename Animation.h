#pragma once
#include <olcPixelGameEngine.h>

olc::Renderable loadImage(const std::filesystem::path& path);
std::vector<olc::Renderable> loadImages(const std::vector<std::filesystem::path>& vecImagePaths);


class Animation
{
public:
	Animation(const std::vector<std::filesystem::path>& vecImagePaths, float frameTime);
	void draw(olc::vf2d pos, float fElepsedTime, olc::PixelGameEngine* pge);

private:
	int updateIndex(int currentIndex, float fElepsedTime);

	std::vector<olc::Renderable> m_vecImages;
	int m_currentImageIndex{ 0 };
	float m_frameTime{1.f};
	float m_time{0.f};
};

