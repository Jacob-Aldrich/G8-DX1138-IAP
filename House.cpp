#include "House.h"
#include "Game.h"

House::House(char sym, int x, int y, std::string name, Game* g) : Object(sym, x, y, name), game(g)
{
}

bool House::Interacted()
{
	game->goInsideHouse();
	return false;
}
