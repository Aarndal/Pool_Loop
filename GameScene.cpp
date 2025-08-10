#include <cassert>
#include "GameScene.h"
#include "PlayerData.h"
#include "PlayerCharacter.h"
#include "SceneManager.h"
#include "Score.h"

namespace
{
	const auto cameraStartPos = [](const olc::PixelGameEngine* engine) {return olc::vf2d{ 0.f, static_cast<float>(engine->GetScreenSize().y) * -5.f }; };
}


GameScene::GameScene(olc::PixelGameEngine* pEngine)
	: m_pEngine{ pEngine }
	, m_startPosition{ cameraStartPos(pEngine) + olc::vf2d{ 550.f,375.f } }
	, m_camera{ cameraStartPos(pEngine) }
{
}

void GameScene::init(const std::shared_ptr<ISceneData>& data)
{
	std::shared_ptr playerData = std::dynamic_pointer_cast<PlayerData>(data);

	assert(playerData);

	if (!m_playerCharacter)
	{
		m_playerCharacter = { m_pEngine, this, std::move(playerData) };
	}

	if (m_playerCharacter->getIsInitialized() == false)
		m_playerCharacter->init(m_startPosition);

	m_background.load();
	Score::getInstance().resetScore();
}

void GameScene::update(const float elapsedTime)
{
	m_pEngine->Clear(olc::WHITE);

	if (m_playerCharacter && m_playerCharacter->getIsInitialized() == true)
	{
		const auto playerHeight = m_playerCharacter->getPosition().y;

		m_playerCharacter->update(elapsedTime);

		m_camera.move({ 0,m_playerCharacter->getPosition().y - playerHeight });
	}

	// Draw
	m_background.drawBG(*m_pEngine, m_camera);

	if (m_playerCharacter && m_playerCharacter->getIsInitialized() == true)
		m_playerCharacter->draw(*m_pEngine, m_camera);

	m_background.drawFG(*m_pEngine, m_camera);
}
