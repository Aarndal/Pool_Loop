#pragma once

#include <olcPixelGameEngine.h>
#include "Camera.h"

class GameSceneBackground
{
public:
	GameSceneBackground(size_t imageCount);
	void load();
	void drawBG(olc::PixelGameEngine& engine, const Camera& camera);
	void drawFG(olc::PixelGameEngine& engine, const Camera& camera);

private:
	std::vector<olc::Renderable> m_vecImagesBG;
	std::vector<olc::Renderable> m_vecImagesFG;
	olc::Renderable m_instructions;
	size_t m_imageCount;
};

