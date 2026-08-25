#include "World.h"
#include <iostream>

#include "Water.h"
#include "Food.h"

#include "Game.h"
#include "Inventory.h"
#include "Equipment.h"

World::World(Game* g) : food(new Material(0, 800, 'F', "Food")), water(new Material(0, 800, 'W', "Water"))
{

	std::cout << "Constructing World\n";
	Days = 0;
    game = g;
}

World::~World()
{
	std::cout << "Destructing World\n";
    DeleteAllObjects();
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

	food->AddQuantity(randomFood);
	water->AddQuantity(randomWater);
}

void World::MovePlayer(char Direction, Player* player)
{
    if (player == nullptr)
    {
        return;
    }
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

    RandomEncounter();
}

void World::InteractWithObject(char keypress, Player* player)
{
    if (player == nullptr)
    {
        return;
    }

    if (keypress != 'e' && keypress != 'E')
    {
        return;
    }

    int playerX = player->GetX();
    int playerY = player->GetY();

    for (int i = 0;
        i < Chunk[CurrentChunk].GetMaxObjects();
        i++)
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

        if (!playerIsNear)
        {
            continue;
        }

        Equipment* equipment =
            dynamic_cast<Equipment*>(obj);

        // -----------------------------
        // EQUIPMENT
        // -----------------------------
        if (equipment != nullptr)
        {
            std::cout << "\nYou found "
                << equipment->GetName()
                << "!\n\n";

            equipment->PrintDetails();

            std::cout << "\n\n";
            std::cout << "[1] Equip\n";
            std::cout << "[2] Store\n";

            char choice;
            std::cin >> choice;

            Inventory& inventory =
                player->GetInventory();

            if (choice == '1')
            {
                if (inventory.GetEquippedGear() != nullptr)
                {
                    std::cout
                        << "You already have "
                        << inventory.GetEquippedGear()->GetName()
                        << " equipped.\n";
                    return;
                }

                if (inventory.EquipEquipment(equipment))
                {
                    Chunk[CurrentChunk].RemoveObject(obj);
                }
            }
            else if (choice == '2')
            {
                if (inventory.AddItem(obj))
                {
                    Chunk[CurrentChunk].RemoveObject(obj);

                    std::cout << equipment->GetName()
                        << " was stored in your inventory.\n";
                }
                else
                {
                    std::cout
                        << "Your inventory is full!\n";
                }
            }

            return;
        }

        // -----------------------------
        // NORMAL OBJECT
        // -----------------------------
        if (obj->Interacted())
        {
            Inventory& inventory =
                player->GetInventory();

            if (inventory.AddItem(obj))
            {
                Chunk[CurrentChunk].RemoveObject(obj);

                std::cout << obj->GetName()
                    << " was added to your inventory.\n";
            }
            else
            {
                std::cout << "Your inventory is full!\n";
            }
        }

        return;
    }
}

void World::displayInteractionOptions(Player* player)
{
    if (player == nullptr)
    {
        return;
    }

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

void World::HandleInventory(char keypress, Player* player)
{
    if (player == nullptr)
    {
        return;
    }

    if (keypress == 'b' || keypress == 'B')
    {
        player->GetInventory().InventoryMenu();
    }
}

void World::HandleKeypress(char keypress, Player* player)
{
    MovePlayer(keypress, player);
    InteractWithObject(keypress, player);
	HandleInventory(keypress, player);
}

void World::RandomEncounter()
{
	int Chance = rand() % 100;
}

void World::CreateObjects()
{
    int ToSpawn = 0;

    for (int i = 0; i < MaxChunk; i++)
    {
        if (i == 0) {
            ToSpawn = Chunk[i].GetMaxObjects()-2;
        }
        else {
            ToSpawn = Chunk[i].GetMaxObjects() - 1;
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

            int randomSupply = rand() % 10;

            if (randomSupply < 4)
            {
                Water* waterObject =
                    new Water(1, 1);

                waterObject->SetX(randX);
                waterObject->SetY(randY);

                Chunk[i].AddObject(waterObject);
            }
            else if (randomSupply < 8)
            {
                Food* foodObject =
                    new Food(1, 1);

                foodObject->SetX(randX);
                foodObject->SetY(randY);

                Chunk[i].AddObject(foodObject);
            }
            else
            {
                int randomEquipment = rand() % 2;

                Equipment* equipment = nullptr;

                if (randomEquipment == 0)
                {
                    equipment = new Equipment(
                        ItemType::SWORD,
                        EquipmentSlot::HAND,
                        "Sword",
                        'S',
                        randX,
                        randY,
                        5,
                        false,
                        false,
                        0
                    );
                }
                else
                {
                    equipment = new Equipment(
                        ItemType::GUN,
                        EquipmentSlot::HAND,
                        "Gun",
                        'G',
                        randX,
                        randY,
                        10,
                        false,
                        true,
                        6
                    );
                }

                Chunk[i].AddObject(equipment);
            }
        }
    }
}

void World::DeleteAllObjects()
{
    for (int i = 0; i < MaxChunk; i++)
    {
        for (int j = 0; j < Chunk[i].GetMaxObjects(); j++)
        {
            Object* obj = Chunk[i].GetObject(j);

            if (obj == nullptr)
            {
                continue;
            }

            std::cout << "Deleting at Chunk "
                << i << ": "
                << obj->GetName()
                << std::endl;
            
            delete obj;
            Chunk[i].RemoveObject(obj);
        }
    }
}

Material* World::GetFood()
{
	return food;
}

Material* World::GetWater()
{
	return water;
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
