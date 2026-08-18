#include "World.h"
#include <iostream>
#include "Material.h"

World::World() : Food(0, 10), Water(0, 10)
{
	CurrentChunk = 1;
	PlayerX = 5;
	PlayerY = 5;
	std::cout << "Constructing World\n";
	Days = 0;
	Turns = 5;
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

void World::MovePlayer(char Direction)
{
    if (Direction == 'w')
    {
        PlayerY--;

        if (PlayerY < 0 && CurrentChunk == 1)
        {
            CurrentChunk = 3;
            PlayerY = 9;
        }
        else if (PlayerY < 0)
        {
            PlayerY = 0;
        }
    }

    else if (Direction == 's')
    {
        PlayerY++;

        if (PlayerY > 9 && CurrentChunk == 1)
        {
            CurrentChunk = 0;
        }
        else if (PlayerY > 9 && CurrentChunk == 3)
        {
            CurrentChunk = 1;
            PlayerY = 0;
        }
        else if (PlayerY > 9)
        {
            PlayerY = 9;
        }
    }

    else if (Direction == 'a')
    {
        PlayerX--;

        if (PlayerX < 0 && CurrentChunk == 1)
        {
            CurrentChunk = 2;
            PlayerX = 9;
        }
        else if (PlayerX < 0 && CurrentChunk == 4)
        {
            CurrentChunk = 1;
            PlayerX = 9;
        }
        else if (PlayerX < 0)
        {
            PlayerX = 0;
        }
    }

    else if (Direction == 'd')
    {
        PlayerX++;

        if (PlayerX > 9 && CurrentChunk == 1)
        {
            CurrentChunk = 4;
            PlayerX = 0;
        }
        else if (PlayerX > 9 && CurrentChunk == 2)
        {
            CurrentChunk = 1;
            PlayerX = 0;
        }
        else if (PlayerX > 9)
        {
            PlayerX = 9;
        }
    }
}

void World::Explore()
{
	char Direction;

	while (true)
	{
		chunks[CurrentChunk - 1].PrintChunk(PlayerX, PlayerY);

		std::cout << "Move with W/A/S/D\n";
		std::cout << "Press E to stop exploring\n";
		std::cout << "Chunk: " << CurrentChunk << "\n";

		std::cin >> Direction;

		if (Direction == 'e')
		{
			return;
		}

		MovePlayer(Direction);
	}
}
World::~World()
{
	std::cout << "Destructing World\n";
}
