#include "Food.h"

Food::Food(int startingQuantity, int startingMaximumQuantity, Material* supply)
    : Material(startingQuantity, startingMaximumQuantity, 'F', "Food"),
    foodSupply(supply)
{
}

bool Food::Interacted()
{
    std::cout << "You interacted with food. You can collect it to increase your food supply.\n";
    foodSupply->AddQuantity(2);
    return true;
}