#include "World.h"
#include <iostream>
World::World() : Food(0,10), Water(0,10) 
{
	std::cout << "Constructing World\n";
	Days = 0;
	Turns = 5;
}

World::~World()
{
	std::cout << "Destructing World\n";
}
