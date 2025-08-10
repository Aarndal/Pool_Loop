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
	void init(olc::PixelGameEngine& engine, const std::shared_ptr<ISceneData>& data) override;
	void update(olc::PixelGameEngine& engine, const float elapsedTime) override;

	[[nodiscard]] float getGravity() const { return m_gravity; }

private:
	olc::vf2d m_startPosition{ 500.f,300.f };

	GameSceneBackground m_background{6};

	std::optional<PlayerCharacter> m_playerCharacter;
	std::optional<Camera> m_camera;

	float m_gravity{ 10.0f };
};
