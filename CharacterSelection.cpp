#include "CharacterSelection.h"
#include "SceneManager.h"
#include "PlayerData.h"

namespace
{
	std::vector<std::string> vecCharacterNames
	{
		/*"Cat_00",*/
		"Cat_01",
		"Cat_02",
		"Cat_03",
		"Cat_04",
		"Cat_05",
		"Cat_06",

	};

	const olc::vf2d buttonSize{144.f,131.f};

	Button createButton(olc::vf2d pos, const std::string& name)
	{
		return { BoundingBox2D{ pos, buttonSize + pos }, "resources\\Icon_"+ name +".png", [=]()
			{
				auto pData = std::make_shared<PlayerData>(1, 0.1f, 75.0f, 120.0f, 200.0f);

				pData->init(
					{
								"resources\\PC_" + name + "_Stretched.png",
								"resources\\PC_" + name + "_Round.png"
					});
				SceneManager::getInstance().changeScene(SceneManager::Scene::game, pData);;
			} };
	}
}



void CharacterSelection::init(olc::PixelGameEngine& , const std::shared_ptr<ISceneData>&)
{
	createButtons();
	loadResources();
}

void CharacterSelection::createButtons()
{
	olc::vf2d pos{ 300,200 };
	for (const auto& name : vecCharacterNames)
	{
		m_vecButtons.emplace_back(createButton(pos, name));
		pos.x += 150;
	}
}

void CharacterSelection::loadResources()
{
	m_backgroundImage.Load("resources\\BG_Menu.png");
	for (auto& button : m_vecButtons)
	{
		button.loadImage();
	}
}

void CharacterSelection::update(olc::PixelGameEngine& engine, float /*time*/)
{
	engine.DrawDecal({}, m_backgroundImage.Decal());

	for (auto& button : m_vecButtons)
	{
		button.update(engine);
	}
}
