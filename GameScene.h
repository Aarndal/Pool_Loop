#pragma once

#include "olcPixelGameEngine.h"
#include "IScene.h"

class GameScene : public IScene
{
public:
	GameScene(olc::PixelGameEngine* engine);
	void init() override;
	void update(float time) override;

private:
	olc::PixelGameEngine* m_engine;
};
