#include "MainMenu.h"
#include "SceneManager.h"

MainMenu::MainMenu(olc::PixelGameEngine* pge) 
	: m_pge{pge}
	, m_vecButtons
	{ 
		{ BoundingBox2D{{870,300},{1205,370}},[=]() {SceneManager::getInstance().changeScene(SceneManager::Scene::game); }},
		{ BoundingBox2D{{870,390},{1205,460}},[=]() {SceneManager::getInstance().changeScene(SceneManager::Scene::characterSelection); }}
	}
{
}

void MainMenu::init()
{
	m_backgroundImage.Load("resources\\Main_Menu.png");
}

void MainMenu::update(float /*time*/)
{
	m_pge->DrawDecal({}, m_backgroundImage.Decal());

	for (const auto& button : m_vecButtons)
	{
		button.draw(m_pge);

		if (m_pge->GetMouse(0).bReleased)
		{
			if (button.hit(m_pge->GetMousePos()))
			{
				button.invoke();
			}
		}
	}
}
