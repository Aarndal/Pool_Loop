#pragma once
#include <olcPixelGameEngine.h>
#include "IScene.h"

class CharacterSelection : public IScene
{
public:
	CharacterSelection(olc::PixelGameEngine* pge);
	void init() override;
	void update(float time) override;
};

