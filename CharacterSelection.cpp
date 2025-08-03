#include "CharacterSelection.h"
#include "SceneManager.h"
#include "PlayerData.h"

namespace
{
	std::vector<std::string> vecCharacterNames
	{
		"Cat_00",
		"Cat_00",
		"Cat_00"
	};

	const olc::vf2d buttonSize{100.f,100.f};

	Button createButton(olc::vf2d pos, const std::string& name)
	{
		return { BoundingBox2D{ pos, buttonSize + pos }, "resources\\Icon_"+ name +".png", [=]()
			{
				auto pData = std::make_shared<PlayerData>(1, 0.5f, 10.0f, 5.0f, 100.0f);

				pData->init(
					{
								"resources\\PC_" + name + "_Stretched.png",
								"resources\\PC_" + name + "_Round.png"
					});
				SceneManager::getInstance().changeScene(SceneManager::Scene::game, pData);;
			} };
	}
}



CharacterSelection::CharacterSelection(olc::PixelGameEngine* pge) : m_pge{pge}
{
	olc::vf2d pos{ 300,300 };
	for (const auto& name : vecCharacterNames)
	{
		m_vecButtons.emplace_back(createButton(pos,name));
		pos.x += 150;
	}
}


void CharacterSelection::init(const std::shared_ptr<ISceneData>&)
{
	m_backgroundImage.Load("resources\\BG_Menu.png");
	for (auto& button : m_vecButtons)
	{
		button.loadImage();
	}
}

void CharacterSelection::update(float /*time*/)
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

//	if (m_pge->GetMouse(0).bReleased)
//	{
//
//		auto pData= std::make_shared<PlayerData>(1, 0.5f, 10.0f, 5.0f, 100.0f );
//
//		pData->init(
//	{
//				"resources\\PC_Cat_00_Stretched.png",
//				"resources\\PC_Cat_00_Round.png"
//		}
//);
//
//		SceneManager::getInstance().changeScene(SceneManager::Scene::game, pData);
//	}
}
