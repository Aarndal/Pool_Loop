#include "GameSceneBackground.h"
#include "Animation.h"
#include "Score.h"

GameSceneBackground::GameSceneBackground(size_t imageCount) : m_imageCount{ imageCount }{}

void GameSceneBackground::load()
{

	m_vecImagesBG = loadImages(
		{
			"resources\\BG_Top.png",
			"resources\\BG_Middle_1.png",
			"resources\\BG_Middle_2.png",
			"resources\\BG_Bottom.png",
		});

	m_vecImagesFG = loadImages(
		{
			"resources\\FG_Top.png",
			"resources\\FG_Bottom.png",
		});

	m_instructions.Load("resources\\Instructions.png");
}


void GameSceneBackground::drawBG(olc::PixelGameEngine& engine, const Camera& camera)
{
	//Draw top
	engine.DrawDecal(camera.transform(olc::vf2d{ 0.f, engine.GetScreenSize().y * -static_cast<float>(m_imageCount-1) }), m_vecImagesBG.front().Decal());

	for (size_t i = 1; i < m_imageCount - 1; ++i)
	{
		const auto offset = olc::vf2d{ 0.f, engine.GetScreenSize().y * -static_cast<float>(m_imageCount - 1 - i) };
		engine.DrawDecal(camera.transform(offset), m_vecImagesBG.at(1+i%2).Decal());
	}

	//Draw Bottom
	engine.DrawDecal(camera.transform({0.f,0.f}), m_vecImagesBG.back().Decal());
}

void GameSceneBackground::drawFG(olc::PixelGameEngine& engine, const Camera& camera)
{
	//Draw top
	engine.DrawDecal(camera.transform(olc::vf2d{ 0.f, engine.GetScreenSize().y * -static_cast<float>(m_imageCount - 1) }), m_vecImagesFG.front().Decal());

	//Draw Bottom
	engine.DrawDecal(camera.transform({ 0.f,0.f }), m_vecImagesFG.back().Decal());

	engine.DrawDecal(camera.transform(
		olc::vf2d{ 0.f, engine.GetScreenSize().y * -static_cast<float>(m_imageCount - 1) } + olc::vf2d{ 100.f,50.f }), m_instructions.Decal());

	//Score
	std::stringstream s;
	s << "Score: " << Score::getInstance().getFinalScore();
	engine.DrawStringDecal(olc::vf2d{ 1100.f,50.f }, s.str(), olc::DARK_GREY, {10.f,10.f});
}
