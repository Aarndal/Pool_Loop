#include "GameScene.h"
#include "PlayerData.h"
#include "PlayerCharacter.h"

GameScene::GameScene(olc::PixelGameEngine* engine) : m_engine{ engine }
{
}

void GameScene::init()
{
	m_gravity = 10.0f;

	PlayerData playerData{ 1, 10.0f, 5.0f, 20.0f };

	if (!m_playerCharacter)
	{
		m_playerCharacter = { &playerData };
	}

	m_playerCharacter->setIsFalling(false);
}

void GameScene::update(float elapsedTime)
{
	m_engine->Clear(olc::VERY_DARK_BLUE);

	if (m_playerCharacter->getIsFalling())
	{
		if (m_engine->GetKey(olc::Key::A).bHeld)
		{
			m_playerCharacter->move(elapsedTime, PlayerCharacter::Movement::LEFT);
		}

		if (m_engine->GetKey(olc::Key::D).bHeld)
		{
			m_playerCharacter->move(elapsedTime, PlayerCharacter::Movement::RIGHT);
		}

		m_pos += olc::vf2d{ 0,1 } *m_gravity * elapsedTime;
	}
	else
	{
		if (m_engine->GetKey(olc::Key::SPACE).bPressed)
		{
			m_playerCharacter->setIsFalling(true);
		}
	}

	olc::vf2d size{ 400.f,50.f };
	m_engine->DrawRectDecal(m_pos, size, olc::RED);
}
