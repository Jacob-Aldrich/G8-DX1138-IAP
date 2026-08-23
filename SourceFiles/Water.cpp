#include "Water.h"

Water::Water(int startingQuantity, int startingMaximumQuantity) : Material(startingQuantity, startingMaximumQuantity, 'W', "Water")
{
}

void Water::Interacted()
{
	std::cout << "You interacted with water. You can collect it to increase your water supply.\n";
}

