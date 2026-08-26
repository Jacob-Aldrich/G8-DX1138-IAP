#include "Water.h"

//junlong
Water::Water(int startingQuantity, int startingMaximumQuantity): Material(startingQuantity,startingMaximumQuantity,'W',"Water")
{
}

bool Water::Interacted()
{
	std::cout << "You collected Water.\n";
	return true;
}