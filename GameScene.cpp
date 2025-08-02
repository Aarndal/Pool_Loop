#include "GameScene.h"

GameScene::GameScene(olc::PixelGameEngine* engine) : m_engine{ engine }
{
}

void GameScene::init()
{
	m_falling = false;
	m_gravitySpeed = 10.0f;
	m_speed = 2.0f;
}

void GameScene::update(float elapsedTime)
{
	m_engine->Clear(olc::VERY_DARK_BLUE);

	if (m_falling)
	{
		if (m_engine->GetKey(olc::Key::A).bHeld)
		{
			m_pos += olc::vf2d{ -1,0 } *m_speed * elapsedTime;
		}

		if (m_engine->GetKey(olc::Key::D).bHeld)
		{
			m_pos += olc::vf2d{ 1,0 } *m_speed * elapsedTime;
		}

		m_pos += olc::vf2d{ 0,1 } *m_gravitySpeed * elapsedTime;
	}

	if (!m_falling)
	{
		if (m_engine->GetKey(olc::Key::SPACE).bPressed)
		{
			m_falling = true;
		}
	}

	olc::vf2d size{ 400.f,50.f };
	m_engine->DrawRectDecal(m_pos, size, olc::RED);
}
