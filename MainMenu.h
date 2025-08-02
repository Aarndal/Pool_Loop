#pragma once
#include <olcPixelGameEngine.h>
#include "IScene.h"

class MainMenu : public IScene
{
public:
	MainMenu(olc::PixelGameEngine* pge);
	void init() override;
	void update(float time) override;
private:
	olc::Renderable m_backgroundImage;
	olc::PixelGameEngine* m_pge;
};

