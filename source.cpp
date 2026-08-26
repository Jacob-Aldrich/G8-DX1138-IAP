#include "Game.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main(void) {
	srand(static_cast<unsigned int>(time(0)));

	{
		Game game;
		game.Run();
	}

	_CrtDumpMemoryLeaks();
	return 0;
}