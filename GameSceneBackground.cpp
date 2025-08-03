#include "GameSceneBackground.h"
#include "Animation.h"


GameSceneBackground::GameSceneBackground(size_t imageCount) : m_imageCount{ imageCount }{}

void GameSceneBackground::load()
{

	m_vecImages = loadImages(
		{
			"resources\\BG_Top.png",
			"resources\\BG_Middle_1.png",
			"resources\\BG_Middle_2.png",
			"resources\\BG_Bottom.png",
		});
}


void GameSceneBackground::draw(olc::PixelGameEngine& engine, const Camera& camera)
{
	//Draw top
	engine.DrawDecal(camera.transform(olc::vf2d{ 0.f, engine.GetScreenSize().y * -static_cast<float>(m_imageCount-1) }), m_vecImages.front().Decal());

	for (size_t i = 1; i < m_imageCount - 1; ++i)
	{
		const auto offset = olc::vf2d{ 0.f, engine.GetScreenSize().y * -static_cast<float>(m_imageCount - 1 - i) };
		engine.DrawDecal(camera.transform(offset), m_vecImages.at(1+i%2).Decal());
	}

	//Draw Bottom
	engine.DrawDecal(camera.transform({0.f,0.f}), m_vecImages.back().Decal());
}