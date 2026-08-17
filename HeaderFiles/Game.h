#pragma once
#include "World.h"
#include <iostream>
class Game
{
	World* world;
	int Turns;
	static int const maxTurns = 5;
public:
	Game();
	void Run();

	int getTurns();
	void useTurn();

	static void clearConsole();
	~Game();
};

