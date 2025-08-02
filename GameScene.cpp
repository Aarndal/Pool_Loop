#include "GameScene.h"

GameScene::GameScene(olc::PixelGameEngine* engine) : m_engine{engine}
{
}

void GameScene::init()
{
}

void GameScene::update(float time)
{
	olc::vf2d pos{ 500.f,300.f };
	olc::vf2d size{ 400.f,50.f };
	m_engine->DrawRectDecal(pos, size, olc::RED);
}
