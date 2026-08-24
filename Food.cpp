#include "Food.h"

Food::Food(int startingQuantity, int startingMaximumQuantity, Material* supply)
    : Material(startingQuantity, startingMaximumQuantity, 'F', "Food"),
    foodSupply(supply)
{
}

bool Food::Interacted()
{
    int randAmount = rand() % 3 + 1;
    std::cout << "You interacted with food. You can collect it to increase your food supply.\n";
    foodSupply->AddQuantity(randAmount);
    return true;
}