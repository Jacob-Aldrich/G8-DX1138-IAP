#include "Food.h"
//junlong

Food::Food(int startingQuantity, int startingMaximumQuantity): Material(startingQuantity, startingMaximumQuantity, 'F', "Food")
{
}

bool Food::Interacted()
{
	std::cout << "You collected Food.\n";
	return true;
}