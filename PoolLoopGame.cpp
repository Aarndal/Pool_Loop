#include "PoolLoopGame.h"
#include "SceneManager.h"
#include "IScene.h"

bool PoolLoopGameEngine::OnUserCreate()
{
	SceneManager::getInstance().changeScene(SceneManager::Scene::mainMenu);
	return true;
}

bool PoolLoopGameEngine::OnUserUpdate(float fElapsedTime)
{
	if(auto* pCurrentScene = SceneManager::getInstance().getCurrentScene(this))
	{
		pCurrentScene->update(fElapsedTime);
	}
	return true;
}
