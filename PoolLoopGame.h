#pragma once
#include <olcPixelGameEngine.h>

class PoolLoopGameEngine : public olc::PixelGameEngine
{
public:
	PoolLoopGameEngine()
	{
		sAppName = "PoolLoop";
	}

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};