#include "GameScene.h"
#include "PlayerData.h"
#include "PlayerCharacter.h"

GameScene::GameScene(olc::PixelGameEngine* engine) : m_engine{ engine }
{
}

void GameScene::init()
{
	PlayerData playerData{ 1, 10.0f, 10.0f, 40.0f };

	playerData.init(
		{
					"resources\\PC_Cat_00_Stretched.png",
					"resources\\PC_Cat_00_Round.png"
		}
	);

	if (!m_playerCharacter)
	{
		m_playerCharacter = { std::move(playerData) };
	}

	m_playerCharacter->init(m_startPosition);

	m_background.Load("resources\\BG_Top.png");
}

void GameScene::update(float elapsedTime)
{
	m_engine->Clear(olc::VERY_DARK_BLUE);

	// Move PlayerCharacter
	if (m_playerCharacter->getIsFalling())
	{
		if (m_engine->GetKey(olc::Key::A).bHeld)
		{
			m_playerCharacter->moveHorizontal(elapsedTime, PlayerCharacter::Movement::LEFT);
		}
		else if (m_engine->GetKey(olc::Key::D).bHeld)
		{
			m_playerCharacter->moveHorizontal(elapsedTime, PlayerCharacter::Movement::RIGHT);
		}
		else
		{
			m_playerCharacter->moveHorizontal(elapsedTime, PlayerCharacter::Movement::NONE);
		}

		m_playerCharacter->moveVertical(elapsedTime, m_gravity);

		m_playerCharacter->rotate(elapsedTime, *m_engine);
	}
	else
	{
		m_playerCharacter->jump(*m_engine);
	}

	// Draw
	m_engine->DrawDecal({}, m_background.Decal());
	m_playerCharacter->draw(*m_engine);

	/*olc::vf2d size{ 50.f,100.f };
	m_engine->DrawRectDecal(m_playerCharacter->getPosition(), size, olc::RED);*/
}
