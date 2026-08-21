#pragma once

#include "Chunks.h"
#include "Material.h"

// All item and equipment types that can appear in the world.
enum class ItemType
{
	Food,
	Water,
	Gun,
	RealKnife
};

enum class EquipmentSlot
{
	None,
	Gear
};

class Player;

// World stores the day, turns, resources and exploration state.
class World
{
private:
	int Days;
	int Turns;
	int CurrentChunk;
	int PlayerX;
	int PlayerY;

	Material Water;
	Material Food;
	Chunks chunks[4];

	void CreateObjects();
	Object* GetNearbyObject();

public:
	World();

	int GetDays();
	int GetTurns();
	int GetCurrentChunk();
	int GetPlayerX();
	int GetPlayerY();

	int GetFoodQuantity();
	int GetWaterQuantity();
	int GetMaximumFood();
	int GetMaximumWater();

	void UseTurn();
	void EndTurns();
	void NextDay();

	bool UseDailySupplies(int peopleToFeed);

	void Explore(Player* player);
	bool MovePlayer(char direction, Player* player = nullptr);
	bool CollectNearbySupply();
	bool CollectNearbyItem(Player* player);
	void ResetExplorationPosition();
	void PrintLegend();

	Chunks& GetChunk(int chunkNumber);
};
