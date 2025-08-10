#pragma once
#include <olcPixelGameEngine.h>
#include "IScene.h"
#include "Button.h"

class CharacterSelection : public IScene
{
public:
	void init(olc::PixelGameEngine& engine, const std::shared_ptr<ISceneData>& data = nullptr) override;
	void update(olc::PixelGameEngine& engine, float time) override;

private:
	void createButtons();
	void loadResources();

	olc::Renderable m_backgroundImage;
	std::vector<Button> m_vecButtons;
};

