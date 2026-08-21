#include "World.h"
#include "Equipment.h"
#include "Player.h"

#include <cctype>
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <limits>

World::World() : Water(5, 10), Food(5, 10)
{
	Days = 1;
	Turns = 5;
	CurrentChunk = 1;
	PlayerX = 5;
	PlayerY = 9;

	for (int i = 0; i < 4; i++)
	{
		chunks[i].SetChunkNumber(i + 1);
	}

	CreateObjects();
}

int World::GetDays()
{
	return Days;
}

int World::GetTurns()
{
	return Turns;
}

int World::GetCurrentChunk()
{
	return CurrentChunk;
}

int World::GetPlayerX()
{
	return PlayerX;
}

int World::GetPlayerY()
{
	return PlayerY;
}

int World::GetFoodQuantity()
{
	return Food.GetQuantity();
}

int World::GetWaterQuantity()
{
	return Water.GetQuantity();
}

int World::GetMaximumFood()
{
	return Food.GetMaximumQuantity();
}

int World::GetMaximumWater()
{
	return Water.GetMaximumQuantity();
}

void World::UseTurn()
{
	if (Turns > 0)
	{
		Turns--;
	}
}

void World::EndTurns()
{
	Turns = 0;
}

void World::NextDay()
{
	Days++;
	Turns = 5;
}

bool World::UseDailySupplies(int peopleToFeed)
{
	bool enoughFood = Food.GetQuantity() >= peopleToFeed;
	bool enoughWater = Water.GetQuantity() >= peopleToFeed;

	if (enoughFood)
	{
		Food.UseQuantity(peopleToFeed);
	}
	else
	{
		Food.UseQuantity(Food.GetQuantity());
	}

	if (enoughWater)
	{
		Water.UseQuantity(peopleToFeed);
	}
	else
	{
		Water.UseQuantity(Water.GetQuantity());
	}

	return enoughFood && enoughWater;
}

void World::ResetExplorationPosition()
{
	CurrentChunk = 1;
	PlayerX = 5;
	PlayerY = 9;
}

bool World::MovePlayer(char direction, Player* player)
{
	direction = static_cast<char>(std::tolower(
		static_cast<unsigned char>(direction)));

	int nextChunk = CurrentChunk;
	int nextX = PlayerX;
	int nextY = PlayerY;

	if (direction == 'w')
	{
		if (nextY > 0)
		{
			nextY--;
		}
		else if (nextChunk == 1)
		{
			nextChunk = 3;
			nextY = 9;
		}
		else
		{
			std::cout << "You cannot travel farther north.\n";
			return true;
		}
	}
	else if (direction == 's')
	{
		if (nextY < 9)
		{
			nextY++;
		}
		else if (nextChunk == 3)
		{
			nextChunk = 1;
			nextY = 0;
		}
		else if (nextChunk == 1)
		{
			CurrentChunk = 0;
			std::cout << "You return home.\n";
			return false;
		}
		else
		{
			std::cout << "You cannot travel farther south.\n";
			return true;
		}
	}
	else if (direction == 'a')
	{
		if (nextX > 0)
		{
			nextX--;
		}
		else if (nextChunk == 1)
		{
			nextChunk = 2;
			nextX = 9;
		}
		else if (nextChunk == 4)
		{
			nextChunk = 1;
			nextX = 9;
		}
		else
		{
			std::cout << "You cannot travel farther west.\n";
			return true;
		}
	}
	else if (direction == 'd')
	{
		if (nextX < 9)
		{
			nextX++;
		}
		else if (nextChunk == 1)
		{
			nextChunk = 4;
			nextX = 0;
		}
		else if (nextChunk == 2)
		{
			nextChunk = 1;
			nextX = 0;
		}
		else
		{
			std::cout << "You cannot travel farther east.\n";
			return true;
		}
	}
	else
	{
		std::cout << "Use W, A, S, D or E.\n";
		return true;
	}

	Object* object = chunks[nextChunk - 1].CheckForObject(nextX, nextY);

	CurrentChunk = nextChunk;
	PlayerX = nextX;
	PlayerY = nextY;

	// Walking onto any map object automatically attempts to collect it.
	if (object != nullptr)
	{
		CollectNearbyItem(player);
	}

	return true;
}

Object* World::GetNearbyObject()
{
	if (CurrentChunk < 1 || CurrentChunk > 4)
	{
		return nullptr;
	}

	int positions[5][2] =
	{
		{ PlayerX, PlayerY },
		{ PlayerX + 1, PlayerY },
		{ PlayerX - 1, PlayerY },
		{ PlayerX, PlayerY + 1 },
		{ PlayerX, PlayerY - 1 }
	};

	for (int i = 0; i < 5; i++)
	{
		Object* object = chunks[CurrentChunk - 1].CheckForObject(
			positions[i][0], positions[i][1]);

		if (object != nullptr)
		{
			return object;
		}
	}

	return nullptr;
}

bool World::CollectNearbySupply()
{
	return CollectNearbyItem(nullptr);
}

bool World::CollectNearbyItem(Player* player)
{
	Object* object = GetNearbyObject();

	if (object == nullptr)
	{
		std::cout << "There is nothing nearby to collect.\n";
		return false;
	}

	Material* material = dynamic_cast<Material*>(object);

	if (material != nullptr && material->GetSymbol() == 'F')
	{
		if (Food.GetQuantity() >= Food.GetMaximumQuantity())
		{
			std::cout << "Food storage is full.\n";
			return false;
		}

		Food.AddQuantity(material->GetQuantity());
		std::cout << "You collect " << material->GetQuantity()
			<< " Food.\n";
	}
	else if (material != nullptr && material->GetSymbol() == 'W')
	{
		if (Water.GetQuantity() >= Water.GetMaximumQuantity())
		{
			std::cout << "Water storage is full.\n";
			return false;
		}

		Water.AddQuantity(material->GetQuantity());
		std::cout << "You collect " << material->GetQuantity()
			<< " Water.\n";
	}
	else
	{
		Equipment* equipment = dynamic_cast<Equipment*>(object);

		if (equipment == nullptr)
		{
			object->Interacted();
			return false;
		}

		if (player == nullptr)
		{
			std::cout << "A player inventory is required to collect gear.\n";
			return false;
		}

		if (!player->AddEquipment(equipment))
		{
			std::cout << "Your gear inventory is full.\n";
			return false;
		}

		chunks[CurrentChunk - 1].RemoveObject(equipment);
		std::cout << "You found " << equipment->GetObjectName()
			<< " and stored it in your gear inventory.\n";
		return true;
	}

	chunks[CurrentChunk - 1].RemoveObject(object);
	delete object;
	return true;
}

void World::CreateObjects()
{
	for (int chunkIndex = 0; chunkIndex < 4; chunkIndex++)
	{
		// Each chunk gets two resources. Chunk 1 also gets the Real Knife,
		// and Chunk 2 gets the only Gun in the world.
		int targetObjectCount = 2;
		if (chunkIndex == 0 || chunkIndex == 1)
		{
			targetObjectCount = 3;
		}

		while (chunks[chunkIndex].GetObjectCount() < targetObjectCount)
		{
			int objectNumber = chunks[chunkIndex].GetObjectCount();
			int xPosition = std::rand() % 8 + 1;
			int yPosition = std::rand() % 8 + 1;

			if (chunks[chunkIndex].CheckForObject(xPosition, yPosition)
				!= nullptr)
			{
				continue;
			}

			Object* item = nullptr;

			if (objectNumber < 2 && std::rand() % 2 == 0)
			{
				item = new Material('F', xPosition, yPosition,
					"Food", 1, 1);
			}
			else if (objectNumber < 2)
			{
				item = new Material('W', xPosition, yPosition,
					"Water", 1, 1);
			}
			else if (chunkIndex == 0)
			{
				item = new Equipment(ItemType::RealKnife,
					EquipmentSlot::Gear, "Real Knife", 'G',
					xPosition, yPosition, 99, false, false, 0);
			}
			else
			{
				item = new Equipment(ItemType::Gun,
					EquipmentSlot::Gear, "Gun", 'G',
					xPosition, yPosition, 12, false, true, 6);
			}

			if (!chunks[chunkIndex].AddObject(item))
			{
				delete item;
			}
		}
	}
}

void World::PrintLegend()
{
	std::cout << "Legend: P = Player, F = Food, W = Water\n";
	std::cout << "        G = Gear\n";
}

Chunks& World::GetChunk(int chunkNumber)
{
	if (chunkNumber < 1 || chunkNumber > 4)
	{
		return chunks[0];
	}

	return chunks[chunkNumber - 1];
}

void World::Explore(Player* player)
{
	if (CurrentChunk == 0)
	{
		ResetExplorationPosition();
	}

	// Remove the Enter key left behind by the numbered main menu.
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	while (true)
	{
		char action;

		chunks[CurrentChunk - 1].PrintChunk(PlayerX, PlayerY);
		PrintLegend();
		std::cout << "W/A/S/D = move, E = return home (no Enter needed)\n> ";
		action = static_cast<char>(_getch());

		action = static_cast<char>(std::tolower(
			static_cast<unsigned char>(action)));

		if (action == 'e')
		{
			CurrentChunk = 0;
			std::cout << "You stop exploring and return home.\n";
			return;
		}
		else if (!MovePlayer(action, player))
		{
			return;
		}
	}
}
