#include "Game.h"

int main(void) {
	srand(static_cast<unsigned int>(time(0)));

	static Game game;
	game.Run();
	return 0;
}