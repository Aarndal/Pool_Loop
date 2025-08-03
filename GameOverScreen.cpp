#include "GameOverScreen.h"
#include "SceneManager.h"

GameOverScreen::GameOverScreen(olc::PixelGameEngine* pge) : m_pge{pge}
{
}

void GameOverScreen::init(const std::shared_ptr<ISceneData>& data)
{
	m_backgroundImage.Load("resources\\BG_Bottom.png");
}

void GameOverScreen::update(float time)
{
	m_pge->DrawDecal({}, m_backgroundImage.Decal());

	m_pge->DrawStringDecal({ 700.f,250.f }, "Game over", olc::DARK_GREY,{10.f,10.f});

	if (m_pge->GetKey(olc::Key::SPACE).bPressed)
	{
		SceneManager::getInstance().changeScene(SceneManager::Scene::mainMenu);
	}
}
