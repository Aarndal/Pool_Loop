#pragma once
#include <olcPixelGameEngine.h>
class Logo
{
public:
	Logo(olc::vf2d pos);
	void update(float fDeltaTime);
	void draw(olc::PixelGameEngine* pge);

	struct Letter
	{
		olc::vf2d pos;
		olc::vf2d posMax;
		olc::vf2d posMin;
		olc::vf2d dir;
		olc::Renderable image;
	};

private:
	void drawLetter(olc::PixelGameEngine* pge, const Logo::Letter& letter);
	void updateLetter(float fDeltaTime, Logo::Letter& letter);
	//Letter L;
	//Letter O_1;
	//Letter O_2;
	//Letter P;
	std::vector<Letter> m_vecLetters;
};

