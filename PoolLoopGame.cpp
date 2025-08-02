#include "PoolLoopGame.h"
#include "SceneManager.h"
#include "IScene.h"

bool PoolLoopGameEngine::OnUserCreate()
{
	SceneManager::getInstance().changeScene(SceneManager::Scene::game, this);
	return true;
}

bool PoolLoopGameEngine::OnUserUpdate(float fElapsedTime)
{
	SceneManager::getInstance().getCurrentScene()->update(fElapsedTime);
	return true;
}
