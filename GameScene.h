#pragma once

#include <olcPixelGameEngine.h>
#include "IScene.h"

class GameScene : public IScene
{
public:
	GameScene(olc::PixelGameEngine* engine);
	void init() override;
	void update(float elapsedTime) override;

private:
	olc::PixelGameEngine* m_engine{};
	olc::vf2d m_pos{ 500.f,300.f };

	bool m_falling{ false };

	float m_gravitySpeed{ 0.0f };
	float m_speed{ 0.0f };
};
