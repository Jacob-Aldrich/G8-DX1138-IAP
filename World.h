#pragma once
#include "Object.h"
#include "Material.h"
#include "Chunks.h"
#include "Player.h"
#include "Entity.h"
#include "House.h"

class World
{
	int Days;
	int CurrentChunk = 0;

	static int const MaxChunk = 5;
	Chunks Chunk[MaxChunk];

	Material* water;
	Material* food;
public:
	World(Game* game);
	~World();

	int getDays();
	void addDays(int daysToAdd);
	void setDays(int daysToSet);
	void SearchForSupplies();

	Material* GetFood();
	Material* GetWater();

	Chunks& GetChunks(int index);
	int getCurrentChunk();
	void GoToChunk(int index);

	void MovePlayer(char Direction, Player* player);
	void InteractWithObject(char keypress,Player* player);
	void displayInteractionOptions(Player* player);
	void HandleKeypress(char keypress, Player* player);

	void CreateObjects();
	void DeleteAllObjects();
};
