#pragma once

#include "olcPixelGameEngine.h"
#include "GameScene.h"

class PoolLoopGameEngine : public olc::PixelGameEngine
{
public:
	PoolLoopGameEngine()
	{
		sAppName = "PoolLoop";
	}

public:
	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;

private:
	GameScene gameScene{ this };

};