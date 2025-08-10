#pragma once
#include <olcPixelGameEngine.h>
#include "IScene.h"

class GameOverScreen : public IScene
{
public:
	void init(olc::PixelGameEngine& engnie, const std::shared_ptr<ISceneData>& data) override;
	void update(olc::PixelGameEngine& engnie, float time) override;
private:
	olc::Renderable m_backgroundImage;
	olc::Renderable m_backgroundImageFG;
};

