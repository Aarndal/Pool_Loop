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
	if (GetKey(olc::Key::ESCAPE).bPressed)
	{
		SceneManager::getInstance().changeScene(SceneManager::Scene::mainMenu);
	}

	if(auto* pCurrentScene = SceneManager::getInstance().getCurrentScene(this))
	{
		pCurrentScene->update(fElapsedTime);
		return true;
	}
	return false;
}
