#pragma once
#include "Object.h"
#include "Material.h"
#include "Chunks.h"

class World
{
	int Days;
	int CurrentChunk = 0;
	Chunks Chunk[5];

	Material* Water;
	Material* Food;
public:
	World();
	~World();

	int getDays();
	void addDays(int daysToAdd);
	void setDays(int daysToSet);
	void SearchForSupplies();

	Material* GetFood();
	Material* GetWater();

	Chunks GetChunks(int index);
	int getCurrentChunk();
};
