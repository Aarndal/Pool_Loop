#pragma once

#include <optional>
#include <olcPixelGameEngine.h>
#include "IScene.h"
#include "PlayerCharacter.h"

class GameScene : public IScene
{

public:
	GameScene(olc::PixelGameEngine* engine);

	void init() override;
	void update(float elapsedTime) override;

private:
	olc::PixelGameEngine* m_engine{};
	olc::vf2d m_pos{ 500.f,300.f };

	std::optional<PlayerCharacter> m_playerCharacter{ };

	float m_gravity{ 0.0f };
	float m_speed{ 0.0f };
};
