#include "Food.h"

Food::Food(int startingQuantity, int startingMaximumQuantity) : Material(startingQuantity, startingMaximumQuantity, 'F', "Food")
{
}

void Food::Interacted()
{
    std::cout << "You interacted with food. You can collect it to increase your food supply.\n";
}