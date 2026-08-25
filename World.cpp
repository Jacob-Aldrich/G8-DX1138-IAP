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
    if (player == nullptr) return;

    int targetX = player->GetX();
    int targetY = player->GetY();
    int targetChunk = CurrentChunk;

    if (Direction == 'w') targetY--;
    else if (Direction == 's') targetY++;
    else if (Direction == 'a') targetX--;
    else if (Direction == 'd') targetX++;
    else return;

    // Handle chunk transitions without moving the player until the
    // destination tile has been checked for an object.
    if (targetY < 0)
    {
        if (CurrentChunk == 0) { targetChunk = 1; targetY = 9; }
        else if (CurrentChunk == 3) { targetChunk = 0; targetY = 9; }
        else targetY = 0;
    }
    else if (targetY > 9)
    {
        if (CurrentChunk == 0) { targetChunk = 3; targetY = 0; }
        else if (CurrentChunk == 1) { targetChunk = 0; targetY = 0; }
        else targetY = 9;
    }

    if (targetX < 0)
    {
        if (CurrentChunk == 0) { targetChunk = 4; targetX = 9; }
        else if (CurrentChunk == 2) { targetChunk = 0; targetX = 9; }
        else targetX = 0;
    }
    else if (targetX > 9)
    {
        if (CurrentChunk == 0) { targetChunk = 2; targetX = 0; }
        else if (CurrentChunk == 4) { targetChunk = 0; targetX = 0; }
        else targetX = 9;
    }

    Object* object = Chunk[targetChunk].CheckForObject(targetX, targetY);
    if (object != nullptr) return;

    Chunk[CurrentChunk].RemoveObject(player);
    CurrentChunk = targetChunk;
    player->SetX(targetX);
    player->SetY(targetY);
    Chunk[CurrentChunk].AddObject(player);

    // Every successful outdoor step has a chance to start a battle.
    if (game != nullptr)
        game->StartRandomEncounter();
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
    if (game != nullptr)
        game->StartRandomEncounter();
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

            // Game owns the player and house. They may be temporarily
            // removed from a chunk and must never be deleted here.
            if (dynamic_cast<Player*>(obj) != nullptr ||
                dynamic_cast<House*>(obj) != nullptr)
            {
                continue;
            }

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
