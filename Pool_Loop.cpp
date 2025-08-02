#include "olcPixelGameEngine.h"
#include "GameScene.h"

// Override base class with your custom functionality
class PoolLoopGame : public olc::PixelGameEngine
{
public:
	PoolLoopGame()
	{
		// Name your application
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override
	{
		gameScene.init();
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		gameScene.update(fElapsedTime);
		return true;
	}

private:
	GameScene gameScene{ this };

};

int main()
{
	PoolLoopGame game;
	if (game.Construct(1920, 1080, 1, 1))
		game.Start();
	return 0;
}