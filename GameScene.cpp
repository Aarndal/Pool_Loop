#include "GameScene.h"
#include "PlayerData.h"
#include "PlayerCharacter.h"

namespace
{
	const auto cameraStartPos = [](olc::PixelGameEngine* engine) {return olc::vf2d{ 0.f, engine->GetScreenSize().y * -5.f }; };
}


GameScene::GameScene(olc::PixelGameEngine* engine)
	: m_engine{ engine }
	, m_startPosition{ cameraStartPos(engine) + olc::vf2d{ 500.f,300.f } }
	, camera{ cameraStartPos(engine) }
{
}

void GameScene::init()
{
	PlayerData playerData{ 1, 10.0f, 10.0f, 5.0f, 100.0f };

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

	m_background.load();
}

void GameScene::update(float elapsedTime)
{
	m_engine->Clear(olc::WHITE);
	const auto playerheight = m_playerCharacter->getPosition().y;

	switch (m_playerCharacter->getCurrentState())
	{
	case PlayerCharacter::State::START:
		if (m_engine->GetKey(olc::Key::SPACE).bPressed)
			m_playerCharacter->jump(elapsedTime, *m_engine);
		break;
	case PlayerCharacter::State::JUMP:
	{
		m_playerCharacter->jump(elapsedTime, *m_engine);
		break;
	}
	case PlayerCharacter::State::FALL:
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
		break;
	}
	case PlayerCharacter::State::END:
	{
		break;
	}
	default:
		break;
	}

	camera.move({ 0,m_playerCharacter->getPosition().y - playerheight });

	// Draw
	m_background.draw(*m_engine, camera);
	m_playerCharacter->draw(*m_engine, camera);

	/*olc::vf2d size{ 50.f,100.f };
	m_engine->DrawRectDecal(m_playerCharacter->getPosition(), size, olc::RED);*/
}
