#include "Water.h"

Water::Water(int startingQuantity, int startingMaximumQuantity, Material* supply) : Material(startingQuantity, startingMaximumQuantity, 'W', "Water"), waterSupply(supply)
{
}

bool Water::Interacted()
{
	int randAmount = rand() % 3 + 1;
	std::cout << "You interacted with water. You can collect it to increase your water supply.\n";
	waterSupply->AddQuantity(randAmount);
	return true;
}

