#include "World.h"
#include <iostream>
World::World()
{
	std::cout << "Constructing World\n";
	Days = 0;
}
void World::SearchForSupplies() {

	int randomFood = rand() % 3;
	int randomWater = rand() % 3;
	
	Food.AddQuantity(randomFood);
	Water.AddQuantity(randomWater);

	int FoodAmount = Food.GetQuantity();
	int WaterAmount = Water.GetQuantity();
	int MaxFoodAmount = Food.GetMaximumQuantity();
	int MaxWaterAmount = Water.GetMaximumQuantity();
	
	std::cout << "Food: " << FoodAmount << "/" << MaxFoodAmount << "\n";
	std::cout << "Water: " << WaterAmount << "/" << MaxWaterAmount << "\n";
}
World::~World()
{
	std::cout << "Destructing World\n";
}

int World::getDays()
{
	return Days;
}
