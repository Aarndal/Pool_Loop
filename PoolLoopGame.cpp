#include "PoolLoopGame.h"

bool PoolLoopGameEngine::OnUserCreate()
{
	gameScene.init();
	return true;
}

bool PoolLoopGameEngine::OnUserUpdate(float fElapsedTime)
{
	gameScene.update(fElapsedTime);
	return true;
}
