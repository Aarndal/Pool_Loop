#pragma once

#include "IScene.h"

class GameScene : public IScene
{
	void init() override;
	void update(float time) override;
};

