#include "Logo.h"


namespace
{
	Logo::Letter createL(olc::vf2d pos)
	{
		Logo::Letter L{ .pos = pos,.posMax = pos + olc::vf2d{650.f,0},.posMin = pos + olc::vf2d{0.f,0},.dir = {1.f,0.f},.image = {} };
		L.image.Load("resources/Title_L.png");
		return L;
	}
	Logo::Letter createO_2(olc::vf2d pos)
	{
		Logo::Letter O_2{ .pos = pos + olc::vf2d{400.f,0},.posMax = pos + olc::vf2d{400.f,50.f},.posMin = pos + olc::vf2d{400.f,-50.f} ,.dir = {0.f,1.f},.image = {} };
		O_2.image.Load("resources/Title_O_2.png");
		return O_2;
	}
	Logo::Letter createO_1(olc::vf2d pos)
	{
		Logo::Letter O_1{ .pos = pos + olc::vf2d{200.f,0},.posMax = pos + olc::vf2d{200.f,50.f},.posMin = pos + olc::vf2d{200.f,-50.f} ,.dir = {0.f,-1.f},.image = {} };
		O_1.image.Load("resources/Title_O_1.png");
		return O_1;
	}
	Logo::Letter createP(olc::vf2d pos)
	{
		Logo::Letter P{ .pos = pos + olc::vf2d{600.f,0},.posMax = pos + olc::vf2d{650.f,0},.posMin = pos + olc::vf2d{0.f,0},.dir = {-1.f,0.f},.image = {} };
		P.image.Load("resources/Title_P.png");
		return P;
	}
}


Logo::Logo(olc::vf2d pos)
{
	m_vecLetters.emplace_back(createL(pos));
	m_vecLetters.emplace_back(createO_1(pos));
	m_vecLetters.emplace_back(createO_2(pos));
	m_vecLetters.emplace_back(createP(pos));
}

void Logo::update(float fDeltaTime)
{
	for (auto& letter : m_vecLetters)
	{
		updateLetter(fDeltaTime, letter);
	}
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
	if (letter.pos.y < letter.posMin.y)
	{
		letter.dir = { 0.f,1.f };
	}
	if (letter.pos.y > letter.posMax.y)
	{
		letter.dir = { 0.f,-1.f };
	}
}


void Logo::draw(olc::PixelGameEngine* pge)
{
	std::ranges::sort(m_vecLetters, std::less{}, [](const Letter& l) {return l.dir.x; });
	for (auto& letter : m_vecLetters)
	{
		drawLetter(pge, letter);
	}
}
