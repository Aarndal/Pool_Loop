#pragma once
#include <olcPixelGameEngine.h>
#include "IScene.h"
#include "Button.h"
#include "Logo.h"

class MainMenu : public IScene
{
public:
	MainMenu(olc::PixelGameEngine* pge);
	void init(const std::shared_ptr<ISceneData>& data = nullptr) override;
	void update(float time) override;
private:
	olc::Renderable m_backgroundImage;
	olc::PixelGameEngine* m_pge;
	std::vector<Button> m_vecButtons;
	std::optional<Logo> m_logo;
};

