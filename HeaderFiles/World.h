#pragma once
#include "Object.h"
#include "Material.h"
#include "Chunks.h"
#include "Player.h"
#include "Entity.h"

class World
{
	int Days;
	int CurrentChunk = 0;

	static int const MaxChunk = 5;
	Chunks Chunk[MaxChunk];

	Material* water;
	Material* food;

	Entity* player = new Entity("Player", 100, 100, false, 'P');
	Object* house = new Object('H', 5, 5, "House");
public:
	World();
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

	void MovePlayer(char Direction);
	void InteractWithObject(char keypress);
	void displayInteractionOptions();
	void HandleKeypress(char keypress);

	void CreateObjects();
};
