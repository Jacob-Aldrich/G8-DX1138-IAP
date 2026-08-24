#include "House.h"

House::House(char sym, int x, int y, std::string name) : Object(sym, x, y, name)
{
}

bool House::Interacted()
{
	return false;
}
