#include "MainMenu.h"
#include "SceneManager.h"

namespace
{
	const olc::vf2d buttonSize{420.f,100.f};
}


MainMenu::MainMenu(olc::PixelGameEngine* pge) 
	: m_pge{pge}
{
	const auto posX = 0.5f * (pge->GetScreenSize().x - buttonSize.x);
	m_vecButtons.emplace_back(BoundingBox2D{ {posX,500},buttonSize + olc::vf2d{870,300}  },"resources\\Button_Start.png", [=]() {SceneManager::getInstance().changeScene(SceneManager::Scene::characterSelection); });
	m_vecButtons.emplace_back(BoundingBox2D{ {posX,650},buttonSize + olc::vf2d{870,500} },"resources\\Button_Quit.png", [=]() {SceneManager::getInstance().changeScene(SceneManager::Scene::quit); });
}

void MainMenu::init(const std::shared_ptr<ISceneData>&)
{
	m_backgroundImage.Load("resources\\BG_Menu.png");
	for (auto& button : m_vecButtons)
	{
		button.loadImage();
	}
	m_logo = Logo{ {500.f,100.f} };
}

void MainMenu::update(float time)
{
	m_pge->DrawDecal({}, m_backgroundImage.Decal());

	for (auto& button : m_vecButtons)
	{
		button.update(m_pge);
	}

	if (m_logo)
	{
		m_logo->update(time);
		m_logo->draw(m_pge);
	}
	
}
