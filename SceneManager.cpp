#include "SceneManager.h"
#include "GameScene.h"
#include "MainMenu.h"
#include "CharacterSelection.h"
#include "GameOverScreen.h"


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
        case gameOver:              return std::make_unique<GameOverScreen>(pge);
        case quit:                  return nullptr;
        }
        return std::make_unique<MainMenu>(pge);
    }
}

SceneManager& SceneManager::getInstance()
{
    static SceneManager instance;
    return instance;
}

void SceneManager::changeScene(Scene newScene, const std::shared_ptr<ISceneData>& data)
{
    m_nextScene = { newScene, data };
}

IScene* SceneManager::getCurrentScene(olc::PixelGameEngine* pge)
{
    if (m_nextScene)
    {
        m_currentScene = createSchene(m_nextScene->id, pge);
        if (m_currentScene)
        {
            m_currentScene->init(m_nextScene->data);
        }
        m_nextScene = std::nullopt;
    }
    return m_currentScene.get();
}
