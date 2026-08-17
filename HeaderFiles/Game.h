#pragma once
#include "World.h"
#include <iostream>
class Game
{
	World* world;
public:
	Game();
	void Run();
	~Game();
};

