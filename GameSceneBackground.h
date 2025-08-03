#pragma once

#include <olcPixelGameEngine.h>
#include "Camera.h"

class GameSceneBackground
{
public:
	GameSceneBackground(size_t imageCount);
	void load();
	void draw(olc::PixelGameEngine& engine, const Camera& camera);

private:
	std::vector<olc::Renderable> m_vecImages;
	size_t m_imageCount;
};

