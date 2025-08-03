#pragma once
#include <olcPixelGameEngine.h>
#include "IScene.h"
#include "Button.h"

class CharacterSelection : public IScene
{
public:
	CharacterSelection(olc::PixelGameEngine* pge);
	void init(const std::shared_ptr<ISceneData>& data = nullptr) override;
	void update(float time) override;

private:
	olc::Renderable m_backgroundImage;
	olc::PixelGameEngine* m_pge;
	std::vector<Button> m_vecButtons;
};

