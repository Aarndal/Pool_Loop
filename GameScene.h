#pragma once

#include <optional>
#include <olcPixelGameEngine.h>
#include "IScene.h"
#include "PlayerCharacter.h"
#include "Camera.h"
#include "GameSceneBackground.h"

class GameScene : public IScene
{

public:
	GameScene(olc::PixelGameEngine* engine);

	void init(const std::shared_ptr<ISceneData>& data) override;
	void update(float elapsedTime) override;

private:
	olc::PixelGameEngine* m_engine{};
	olc::vf2d m_startPosition{ 500.f,300.f };

	GameSceneBackground m_background{6};

	std::optional<PlayerCharacter> m_playerCharacter{ };

	float m_gravity{ 10.0f };

	Camera camera;
};
