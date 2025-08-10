#include "MainMenu.h"
#include "SceneManager.h"

namespace
{
	const olc::vf2d buttonSize{420.f,100.f};
}

void MainMenu::init(olc::PixelGameEngine& engine, const std::shared_ptr<ISceneData>&)
{
	const auto posX = 0.5f * (engine.ScreenWidth() - buttonSize.x);
	const olc::vf2d posStart = { posX,500 };
	const olc::vf2d posQuit = { posX,650 };

	m_vecButtons.emplace_back(BoundingBox2D{ posStart,buttonSize + posStart }, "resources\\Button_Start.png", [=]() {SceneManager::getInstance().changeScene(SceneManager::Scene::characterSelection); });
	m_vecButtons.emplace_back(BoundingBox2D{ posQuit,buttonSize + posQuit }, "resources\\Button_Quit.png", [=]() {SceneManager::getInstance().changeScene(SceneManager::Scene::quit); });

	m_backgroundImage.Load("resources\\BG_Menu.png");
  
	for (auto& button : m_vecButtons)
	{
		button.loadImage();
	}
	m_logo = Logo{ {500.f,100.f} };
}

void MainMenu::update(olc::PixelGameEngine& engine, float time)
{
    engine.DrawDecal({}, m_backgroundImage.Decal());

	for (auto& button : m_vecButtons)
	{
		button.update(engine);
	}

	if (m_logo)
	{
		m_logo->update(time);
		m_logo->draw(&engine);
	}
	
}
