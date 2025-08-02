#include "MainMenu.h"
#include "SceneManager.h"

MainMenu::MainMenu(olc::PixelGameEngine* pge) 
	: m_pge{pge}
{
	m_vecButtons.emplace_back(BoundingBox2D{ {870,300},{1205,370} },"resources\\Button_Start.png", [=]() {SceneManager::getInstance().changeScene(SceneManager::Scene::game); });
	m_vecButtons.emplace_back(BoundingBox2D{ {870,390},{1205,460} },"resources\\Button_Character.png", [=]() {SceneManager::getInstance().changeScene(SceneManager::Scene::characterSelection); });
	m_vecButtons.emplace_back(BoundingBox2D{ {870,500},{1205,580} },"resources\\Button_Quit.png", [=]() {SceneManager::getInstance().changeScene(SceneManager::Scene::quit); });
}

void MainMenu::init()
{
	m_backgroundImage.Load("resources\\Main_Menu.png");
	for (auto& button : m_vecButtons)
	{
		button.loadImage();
	}
}

void MainMenu::update(float /*time*/)
{
	m_pge->DrawDecal({}, m_backgroundImage.Decal());

	for (auto& button : m_vecButtons)
	{
		if (button.hit(m_pge->GetMousePos()))
		{
			if (m_pge->GetMouse(0).bReleased && button.m_bPressed)
			{
				if (button.hit(m_pge->GetMousePos()))
				{
					button.invoke();
				}
			}
			const auto mouseState = m_pge->GetMouse(0);
			if (mouseState.bHeld || mouseState.bPressed)
			{
				button.draw(m_pge, Button::DrawingState::pressed);
				button.m_bPressed = true;
			}
			else
			{
				button.draw(m_pge, Button::DrawingState::highlight);
				button.m_bPressed = false;
			}
		}
		else
		{
			button.draw(m_pge);
		}


	}
}
