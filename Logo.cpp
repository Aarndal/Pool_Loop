#include "Logo.h"


Logo::Logo(olc::vf2d pos) :
	L{ .pos = pos,.posMax = pos + olc::vf2d{600.f,0},.posMin = pos,.dir = {1.f,0.f},.image = {} },
	O_1{ .pos = pos + olc::vf2d{200.f,0},.posMax = pos + olc::vf2d{600.f,0},.posMin = pos ,.dir = {0.f,0.f},.image = {} },
	O_2{ .pos = pos + olc::vf2d{400.f,0},.posMax = pos + olc::vf2d{600.f,0},.posMin = pos ,.dir = {0.f,0.f},.image = {} },
	P{ .pos = pos + olc::vf2d{600.f,0},.posMax = pos + olc::vf2d{600.f,0},.posMin = pos ,.dir = {-1.f,0.f},.image = {} }
{
	L.image.Load("resources\\Title_L.png");
	O_1.image.Load("resources\\Title_O_1.png");
	O_2.image.Load("resources\\Title_O_2.png");
	P.image.Load("resources\\Title_P.png");
}

void Logo::update(float fDeltaTime)
{
	updateLetter(fDeltaTime,L);
	updateLetter(fDeltaTime, O_1);
	updateLetter(fDeltaTime, O_2);
	updateLetter(fDeltaTime, P);
}


void Logo::drawLetter(olc::PixelGameEngine* pge, const Logo::Letter& letter)
{
	pge->DrawDecal(letter.pos, letter.image.Decal());
}

void Logo::updateLetter(float fDeltaTime, Logo::Letter& letter)
{
	const float speed = 100.f;
	letter.pos += letter.dir * fDeltaTime * speed;
	if (letter.pos.x < letter.posMin.x)
	{
		letter.dir = { 1.f,0.f };
	}
	if (letter.pos.x > letter.posMax.x)
	{
		letter.dir = { -1.f,0.f };
	}
}


void Logo::draw(olc::PixelGameEngine* pge)
{
	drawLetter(pge, P);	
	drawLetter(pge, O_2);
	drawLetter(pge, O_1);
	drawLetter(pge, L);
}
