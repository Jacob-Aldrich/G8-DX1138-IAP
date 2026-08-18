#include "World.h"
#include <iostream>
World::World() : Food(new Material(0, 10)), Water(new Material(0, 10))
{
	std::cout << "Constructing World\n";
	Days = 0;
}

World::~World()
{
	std::cout << "Destructing World\n";
}

int World::getDays()
{
	return Days;
}

void World::addDays(int daysToAdd)
{
	Days += daysToAdd;
	std::cout << "Adding days to world: " << daysToAdd << "\n";
}

void World::setDays(int daysToSet)
{
	Days = daysToSet;
}

void World::SearchForSupplies()
{
	int randomFood = rand() % 3;
	int randomWater = rand() % 3;

	Food->AddQuantity(randomFood);
	Water->AddQuantity(randomWater);
}

Material* World::GetFood()
{
	return Food;
}

Material* World::GetWater()
{
	return Water;
}

Chunks World::GetChunks(int index)
{
	return Chunk[index];
}

int World::getCurrentChunk()
{
	return CurrentChunk;
}
