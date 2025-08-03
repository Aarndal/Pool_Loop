#include "GameOverScreen.h"
#include "SceneManager.h"
#include "Score.h"

GameOverScreen::GameOverScreen(olc::PixelGameEngine* pge) : m_pge{pge}
{
}

void GameOverScreen::init(const std::shared_ptr<ISceneData>& )
{
	m_backgroundImage.Load("resources\\BG_Bottom.png");
	m_backgroundImageFG.Load("resources\\FG_Bottom.png");
}

void GameOverScreen::update(float )
{
	m_pge->DrawDecal({}, m_backgroundImage.Decal());

	m_pge->DrawStringDecal({ 700.f,250.f }, "Game over", olc::DARK_GREY,{10.f,10.f});
	//Score
	{
		std::stringstream s;
		s << "Score: " << Score::getInstance().getFinalScore();
		m_pge->DrawStringDecal(olc::vf2d{ 700.f,350.f }, s.str(), olc::DARK_GREY, { 10.f,10.f });
	}
	{
		std::stringstream s;
		s << "Highscore: " << Score::getInstance().getHighScore();
		m_pge->DrawStringDecal(olc::vf2d{ 700.f,450.f }, s.str(), olc::DARK_GREY, { 10.f,10.f });

		m_pge->DrawDecal({}, m_backgroundImageFG.Decal());
	}

	if (m_pge->GetKey(olc::Key::SPACE).bPressed)
	{
		SceneManager::getInstance().changeScene(SceneManager::Scene::mainMenu);
	}
}
