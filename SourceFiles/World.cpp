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
    int NewChunk = CurrentChunk;

    if (Direction == 'w')
    {
        PlayerY--;

        if (PlayerY < 0)
        {
            if (CurrentChunk == 0)
            {
                NewChunk = 1;
                PlayerY = 9;
            }
            else if (CurrentChunk == 3)
            {
                NewChunk = 0;
                PlayerY = 9;
            }
            else
            {
                PlayerY = 0;
            }
        }
    }

    else if (Direction == 's')
    {
        PlayerY++;

        if (PlayerY > 9)
        {
            if (CurrentChunk == 0)
            {
                NewChunk = 3;
                PlayerY = 0;
            }
            else if (CurrentChunk == 1)
            {
                NewChunk = 0;
                PlayerY = 0;
            }
            else
            {
                PlayerY = 9;
            }
        }
    }

    else if (Direction == 'a')
    {
        PlayerX--;

        if (PlayerX < 0)
        {
            if (CurrentChunk == 0)
            {
                NewChunk = 4;
                PlayerX = 9;
            }
            else if (CurrentChunk == 2)
            {
                NewChunk = 0;
                PlayerX = 9;
            }
            else
            {
                PlayerX = 0;
            }
        }
    }

    else if (Direction == 'd')
    {
        PlayerX++;

        if (PlayerX > 9)
        {
            if (CurrentChunk == 0)
            {
                NewChunk = 2;
                PlayerX = 0;
            }
            else if (CurrentChunk == 4)
            {
                NewChunk = 0;
                PlayerX = 0;
            }
            else
            {
                PlayerX = 9;
            }
        }
    }

    // Check the destination BEFORE moving the player
    Object* object = Chunk[NewChunk].CheckForObject(PlayerX, PlayerY);

    if (object)
    {
        return;
    }

    // Now actually move the player
    if (NewChunk != CurrentChunk)
    {
        Chunk[CurrentChunk].RemoveObject(player);
        CurrentChunk = NewChunk;
        Chunk[CurrentChunk].AddObject(player);
    }

    player->SetX(PlayerX);
    player->SetY(PlayerY);
}

void World::InteractWithObject(char keypress)
{
    if (keypress != 'e' && keypress != 'E')
    {
        return;
    }

    int playerX = player->GetX();
    int playerY = player->GetY();

    for (int i = 0; i < Chunk[CurrentChunk].GetMaxObjects(); i++)
    {
        Object* obj = Chunk[CurrentChunk].GetObject(i);

        if (obj == nullptr)
        {
            continue;
        }

        int objectX = obj->GetX();
        int objectY = obj->GetY();

        bool playerIsNear =
            (objectX == playerX + 1 && objectY == playerY) ||
            (objectX == playerX - 1 && objectY == playerY) ||
            (objectX == playerX && objectY == playerY + 1) ||
            (objectX == playerX && objectY == playerY - 1);

        if (playerIsNear == false)
        {
            continue;
        }
        if (obj) {
            obj->Interacted();
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
    int ToSpawn = 0;

    for (int i = 0; i < MaxChunk; i++)
    {
        if (i == 0) {
            ToSpawn = 4;
        }
        else {
            ToSpawn = 5;
        }
        for (int j = 0; j < ToSpawn; j++)
        {
            int randX;
            int randY;

            // Keep generating coordinates until an empty position is found
            do
            {
                randX = rand() % Chunk[i].GetBoardSize();
                randY = rand() % Chunk[i].GetBoardSize();
            } while (Chunk[i].CheckForObject(randX, randY) != nullptr);

            int randomSupply = rand() % 2;

            if (randomSupply == 0)
            {
                Object* water = new Object('W', randX, randY, "Water");
                Chunk[i].AddObject(water);
            }
            else
            {
                Object* food = new Object('F', randX, randY, "Food");
                Chunk[i].AddObject(food);
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