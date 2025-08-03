#include <olcPixelGameEngine.h>
#include "PoolLoopGame.h"

int main()
{
	PoolLoopGameEngine game;
	if (game.Construct(1920, 1080, 1, 1,true))
		game.Start();
	return 0;
}