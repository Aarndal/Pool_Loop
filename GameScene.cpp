#include "GameScene.h"
#include "PlayerData.h"
#include "PlayerCharacter.h"
#include "SceneManager.h"
#include <cassert>
#include "Score.h"

namespace
{
	const auto cameraStartPos = [](olc::PixelGameEngine* engine) {return olc::vf2d{ 0.f, engine->GetScreenSize().y * -5.f }; };
}


GameScene::GameScene(olc::PixelGameEngine* engine)
	: m_engine{ engine }
	, m_startPosition{ cameraStartPos(engine) + olc::vf2d{ 500.f,400.f } }
	, camera{ cameraStartPos(engine)}
{
}

void GameScene::init(const std::shared_ptr<ISceneData>& data)
{
	std::shared_ptr playerData = std::dynamic_pointer_cast<PlayerData>(data);

	assert(playerData);

	if (!m_playerCharacter)
	{
		m_playerCharacter = { std::move(playerData) };
	}

	m_playerCharacter->init(m_startPosition);

	m_background.load();
	Score::getInstance().resetScore();
}

void GameScene::update(float elapsedTime)
{
	m_engine->Clear(olc::WHITE);
	const auto playerheight = m_playerCharacter->getPosition().y;

	// Check playerCharacter state and handle input
	switch (m_playerCharacter->getCurrentState())
	{
	case PlayerCharacter::State::START:
		if (m_engine->GetKey(olc::Key::SPACE).bPressed)
			m_playerCharacter->jump();
		break;
	case PlayerCharacter::State::JUMP:
	{
		m_playerCharacter->moveVertical(elapsedTime, m_gravity);
		break;
	}
	case PlayerCharacter::State::FALL:
	{
		m_playerCharacter->rotate(elapsedTime, *m_engine);

		m_playerCharacter->moveVertical(elapsedTime, m_gravity);
		
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

		break;
	}
	case PlayerCharacter::State::END:
	{
		const float targetPosX = 1920 - 1600 + 0.5 * 1600;

		Score::getInstance().finaliseScore(
			m_playerCharacter->getCurrentRotationAngle(),
			m_playerCharacter->getIsRotating(),
			std::abs(m_playerCharacter->getPosition().x - targetPosX));
		SceneManager::getInstance().changeScene(SceneManager::Scene::gameOver);
		break;
	}
	default:
		break;
	}

	camera.move({ 0,m_playerCharacter->getPosition().y - playerheight });

	// Draw
	m_background.drawBG(*m_engine, camera);
	m_playerCharacter->draw(*m_engine, camera);
	m_background.drawFG(*m_engine, camera);
	/*olc::vf2d size{ 50.f,100.f };
	m_engine->DrawRectDecal(m_playerCharacter->getPosition(), size, olc::RED);*/
}
