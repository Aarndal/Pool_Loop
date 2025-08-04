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
	GameScene(olc::PixelGameEngine* pEngine);

	void init(const std::shared_ptr<ISceneData>& data) override;
	void update(const float elapsedTime) override;

	[[nodiscard]] float getGravity() const { return m_gravity; }

private:
	olc::PixelGameEngine* m_pEngine{};
	olc::vf2d m_startPosition{ 500.f,300.f };

	GameSceneBackground m_background{6};

	std::optional<PlayerCharacter> m_playerCharacter{ };

	Camera m_camera;

	float m_gravity{ 10.0f };
};
