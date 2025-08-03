#include "Logo.h"


Logo::Logo(olc::vf2d pos) :
	L{ pos,{} },
	O_1{ pos + olc::vf2d{300.f,0},{} },
	O_2{ pos + olc::vf2d{600.f,0},{} },
	P{ pos + olc::vf2d{900.f,0},{} }
{
	L.image.Load("resources\\Title_L.png");
	O_1.image.Load("resources\\Title_O_1.png");
	O_2.image.Load("resources\\Title_O_2.png");
	P.image.Load("resources\\Title_P.png");
}

void Logo::update(float /*fDeltaTime*/)
{

}


void Logo::drawLetter(olc::PixelGameEngine* pge, const Logo::Letter& letter)
{
	pge->DrawDecal(letter.pos, letter.image.Decal());
}


void Logo::draw(olc::PixelGameEngine* pge)
{
	drawLetter(pge, L);
	drawLetter(pge, O_1);
	drawLetter(pge, O_2);
	drawLetter(pge, P);
}
