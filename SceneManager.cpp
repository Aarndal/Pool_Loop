#include "SceneManager.h"
#include "GameScene.h"
#include "MainMenu.h"
#include "CharacterSelection.h"
#include "GameOverScreen.h"


namespace
{
    std::unique_ptr<IScene> createSchene(SceneManager::Scene newSchene)
    {
        using enum SceneManager::Scene;
        switch (newSchene)
        {
        case mainMenu:              return std::make_unique<MainMenu>();
        case characterSelection:    return std::make_unique<CharacterSelection>();
        case game:                  return std::make_unique<GameScene>();
        case gameOver:              return std::make_unique<GameOverScreen>();
        case quit:                  return nullptr;
        }
        return std::make_unique<MainMenu>();
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

IScene* SceneManager::getCurrentScene(olc::PixelGameEngine& pge)
{
    if (m_nextScene)
    {
        m_currentScene = createSchene(m_nextScene->id);
        if (m_currentScene)
        {
            m_currentScene->init(pge, m_nextScene->data);
        }
        m_nextScene = std::nullopt;
    }
    return m_currentScene.get();
}
