#include "World.h"
#include <iostream>


World::World() : Food(new Material(0, 800, 'F', "Food")), Water(new Material(0, 800, 'W', "Water"))
{
	std::cout << "Constructing World\n";
	Days = 0;

	Chunk[0].AddObject(player);
    player->SetX(5);
    player->SetY(6);

	Chunk[0].AddObject(house);
    CreateObjects();
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

void World::MovePlayer(char Direction)
{
    int PlayerY = player->GetY();
    int PlayerX = player->GetX();

    if (Direction == 'w')
    {
        PlayerY--;
        if (PlayerY < 0 && CurrentChunk == 0)
        {
            Chunk[0].RemoveObject(player);
            CurrentChunk = 1;
            Chunk[1].AddObject(player);

            PlayerY = 9;
        }
        else if (PlayerY < 0 && CurrentChunk == 3)
        {
            Chunk[3].RemoveObject(player);
            CurrentChunk = 0;
            Chunk[0].AddObject(player);

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

        if (PlayerY > 9 && CurrentChunk == 0)
        {
            Chunk[0].RemoveObject(player);
            CurrentChunk = 3;
            Chunk[3].AddObject(player);

            PlayerY = 0;
        }
        else if (PlayerY > 9 && CurrentChunk == 1)
        {
            Chunk[1].RemoveObject(player);
            CurrentChunk = 0;
            Chunk[0].AddObject(player);

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
        if (PlayerX < 0 && CurrentChunk == 0)
        {
            Chunk[0].RemoveObject(player);
            CurrentChunk = 4;
            Chunk[4].AddObject(player);

            PlayerX = 9;
        }
        else if (PlayerX < 0 && CurrentChunk == 2)
        {
            Chunk[2].RemoveObject(player);
            CurrentChunk = 0;
            Chunk[0].AddObject(player);

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
        if (PlayerX > 9 && CurrentChunk == 0)
        {
            Chunk[0].RemoveObject(player);
            CurrentChunk = 2;
            Chunk[2].AddObject(player);

            PlayerX = 0;
        }
        else if (PlayerX > 9 && CurrentChunk == 4)
        {
            Chunk[4].RemoveObject(player);
            CurrentChunk = 0;
            Chunk[0].AddObject(player);

            PlayerX = 0;
        }
        else if (PlayerX > 9)
        {
            PlayerX = 9;
        }
    }

	Object* object = Chunk[CurrentChunk].CheckForObject(PlayerX, PlayerY);
    if (object)
    {
        return;
    }

    player->SetX(PlayerX);
    player->SetY(PlayerY);
}

void World::InteractWithObject(char keypress)
{
	if (keypress == 'e')
	{
        int playerX = player->GetX();
        int playerY = player->GetY();

        for (int i = 0; i < 6; i++)
        {
            Object* obj = Chunk[CurrentChunk].GetObject(i);

            if (obj == nullptr) {
                continue;
            }

            int objectX = obj->GetX();
            int objectY = obj->GetY();

            if ((objectX == playerX + 1 && objectY == playerY) ||
                (objectX == playerX - 1 && objectY == playerY) ||
                (objectX == playerX && objectY == playerY + 1) ||
                (objectX == playerX && objectY == playerY - 1))
            {
                obj->Interacted();
                return;
            }
        }
	}
}

void World::displayInteractionOptions()
{
    int playerX = player->GetX();
    int playerY = player->GetY();

    for (int i = 0; i < 6; i++)
    {
        Object* obj = Chunk[CurrentChunk].GetObject(i);

        if (obj == nullptr) {
            continue;
        }

        int objectX = obj->GetX();
        int objectY = obj->GetY();

        if ((objectX == playerX + 1 && objectY == playerY) ||
            (objectX == playerX - 1 && objectY == playerY) ||
            (objectX == playerX && objectY == playerY + 1) ||
            (objectX == playerX && objectY == playerY - 1))
        {
			std::cout << "You are near " << obj->GetName() << ". Press 'e' to interact.\n";
            return;
        }
    }
}

void World::HandleKeypress(char keypress)
{
    MovePlayer(keypress);
    InteractWithObject(keypress);
}

void World::CreateObjects()
{
    for (int i = 0; i < MaxChunk; i++) {
        for (int j = 0; j < Chunk[i].GetMaxObjects() - Chunk[i].GetObjectCount(); j++) {
            Object* Water;
            Object* Food;
            int randomSupply = rand() % 2;
            int randX, randY;
            randX = rand() % Chunk[i].GetBoardSize();
            randY = rand() & Chunk[i].GetBoardSize();
            while (Chunk[i].CheckForObject(randX, randY)) {
                randX = rand() % Chunk[i].GetBoardSize();
                randY = rand() & Chunk[i].GetBoardSize();
            }

            switch (randomSupply) {
            case 0:
                Water = new Object('W', randX, randY, "Water");
                Chunk[i].AddObject(Water);
                std::cout << Water << " " << randX << ", " << randY << "\n Chunk: " << i << std::endl;
                break;
            case 1:
                Food = new Object('F', randX, randY, "Fire");
                Chunk[i].AddObject(Food);
                std::cout << Food << " " << randX << ", " << randY << "\n Chunk: " << i << std::endl;
                break;
            }
        }
    }
}

Material* World::GetFood()
{
	return Food;
}

Material* World::GetWater()
{
	return Water;
}

Chunks& World::GetChunks(int index)
{
    return Chunk[index];
}

int World::getCurrentChunk()
{
	return CurrentChunk;
}

void World::GoToChunk(int index)
{
	CurrentChunk = index;
}
