#include <cassert>
#include "GameScene.h"
#include "PlayerData.h"
#include "PlayerCharacter.h"
#include "SceneManager.h"
#include "Score.h"

namespace
{
	auto cameraStartPos(const olc::PixelGameEngine& engine) 
	{
		return olc::vf2d{ 0.f, static_cast<float>(engine.GetScreenSize().y) * -5.f }; 
	};
}


void GameScene::init(olc::PixelGameEngine& engine, const std::shared_ptr<ISceneData>& data)
{
	std::shared_ptr playerData = std::dynamic_pointer_cast<PlayerData>(data);

	assert(playerData);

	m_startPosition = { cameraStartPos(engine) + olc::vf2d{ 550.f,375.f } };
	m_camera = { cameraStartPos(engine) };

	if (!m_playerCharacter)
	{
		const auto inputHandler = InputHandler(&engine);
		m_playerCharacter = { std::move(playerData), inputHandler, m_startPosition };
	}

	m_background.load();
	Score::getInstance().resetScore();
}

void GameScene::update(olc::PixelGameEngine& engine, const float elapsedTime)
{
	engine.Clear(olc::WHITE);
	if (!m_camera)
	{
		return;
	}


	if (m_playerCharacter)
	{
		const auto playerHeight = m_playerCharacter->getPosition().y;

		m_playerCharacter->update(elapsedTime, *this);

		m_camera->move({ 0,m_playerCharacter->getPosition().y - playerHeight });
	}

	// Draw
	m_background.drawBG(engine, *m_camera);

	if (m_playerCharacter)
		m_playerCharacter->draw(engine, *m_camera);

	m_background.drawFG(engine, *m_camera);
}
