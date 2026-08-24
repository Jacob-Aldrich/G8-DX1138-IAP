#include "Water.h"

Water::Water(int startingQuantity, int startingMaximumQuantity, Material* waterSupply) : Material(startingQuantity, startingMaximumQuantity, 'W', "Water")
{
}

bool Water::Interacted()
{
	std::cout << "You interacted with water. You can collect it to increase your water supply.\n";
	return true;
}

