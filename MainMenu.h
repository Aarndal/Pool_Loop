#pragma once
#include <olcPixelGameEngine.h>
#include "IScene.h"
#include "Button.h"
#include "Logo.h"

class MainMenu : public IScene
{
public:
	void init(olc::PixelGameEngine& engine, const std::shared_ptr<ISceneData>& data = nullptr) override;
	void update(olc::PixelGameEngine& engine, float time) override;
private:
	olc::Renderable m_backgroundImage;
	std::vector<Button> m_vecButtons;
	std::optional<Logo> m_logo;
};

