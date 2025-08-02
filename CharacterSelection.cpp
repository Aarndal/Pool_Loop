#include "CharacterSelection.h"
#include "SceneManager.h"
CharacterSelection::CharacterSelection(olc::PixelGameEngine* pge) : m_pge{pge}
{

}


void CharacterSelection::init()
{
	m_backgroundImage.Load("resources\\Character_Menu.png");
}

void CharacterSelection::update(float /*time*/)
{
	m_pge->DrawDecal({}, m_backgroundImage.Decal());

	if (m_pge->GetMouse(0).bReleased)
	{
		SceneManager::getInstance().changeScene(SceneManager::Scene::game);
	}
}
