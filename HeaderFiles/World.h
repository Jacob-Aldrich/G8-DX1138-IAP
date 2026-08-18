#pragma once
#include "Object.h"
class World
{
	int Days;
	int Place[5];
	Object* Objects[10];

	Material Water;
	Material Food;

public:
	World();

	void SearchForSupplies();

	~World();

	int getDays();
};

