#pragma once
#include <olcPixelGameEngine.h>
#include "IScene.h"

class GameOverScreen : public IScene
{
public:
	GameOverScreen(olc::PixelGameEngine* pge);
	void init(const std::shared_ptr<ISceneData>& data) override;
	void update(float time) override;
private:
	olc::Renderable m_backgroundImage;
	olc::PixelGameEngine* m_pge;
};

