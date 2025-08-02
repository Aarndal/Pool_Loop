#include "SceneManager.h"
#include "GameScene.h"
#include "MainMenu.h"
#include "CharacterSelection.h"


namespace
{
    std::unique_ptr<IScene> createSchene(SceneManager::Scene newSchene, olc::PixelGameEngine* pge)
    {
        using enum SceneManager::Scene;
        switch (newSchene)
        {
        case mainMenu:              return std::make_unique<MainMenu>(pge);
        case characterSelection:    return std::make_unique<CharacterSelection>(pge);
        case game:                  return std::make_unique<GameScene>(pge);
        }
        return std::make_unique<MainMenu>(pge);
    }
}

SceneManager& SceneManager::getInstance()
{
    static SceneManager instance;
    return instance;
}

void SceneManager::changeScene(Scene newScene, olc::PixelGameEngine* pge)
{
    m_currentScene = createSchene(newScene, pge);
    m_currentScene->init();
}

IScene* SceneManager::getCurrentScene()
{
    return m_currentScene.get();
}
