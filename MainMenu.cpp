#include "MainMenu.h"
#include "SceneManager.h"

MainMenu::MainMenu(olc::PixelGameEngine* pge) :m_pge{pge}
{
}

void MainMenu::init()
{
	m_backgroundImage.Load("resources\\Main_Menu.png");
}

void MainMenu::update(float /*time*/)
{
	m_pge->DrawDecal({}, m_backgroundImage.Decal());

	if (m_pge->GetMouse(0).bReleased)
	{
		SceneManager::getInstance().changeScene(SceneManager::Scene::characterSelection, m_pge);
	}
}
