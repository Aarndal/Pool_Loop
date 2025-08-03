#pragma once
#include <olcPixelGameEngine.h>
class Logo
{
public:
	Logo(olc::vf2d pos);
	void update(float fDeltaTime);
	void draw(olc::PixelGameEngine* pge);
private:

	struct Letter
	{
		olc::vf2d pos;
		olc::Renderable image;
	};
	void drawLetter(olc::PixelGameEngine* pge, const Logo::Letter& letter);

	Letter L;
	Letter O_1;
	Letter O_2;
	Letter P;
};

