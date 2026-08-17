#pragma once
#include "Object.h"
class World
{
	int Days;
	int Place[5];
	Object* Objects[10];
public:
	World();
	~World();

	int getDays();
};

