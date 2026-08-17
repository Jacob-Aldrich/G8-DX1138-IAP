#include "World.h"
#include <iostream>
World::World()
{
	std::cout << "Constructing World\n";
	Days = 0;
}

World::~World()
{
	std::cout << "Destructing World\n";
}

int World::getDays()
{
	return Days;
}
