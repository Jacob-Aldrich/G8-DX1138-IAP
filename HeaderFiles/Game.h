#pragma once
#include "World.h"
#include "Entity.h"
#include "endings.h"
#include <iostream>
#include <conio.h>
class Game
{
	World* world;
	int Turns;
	static int const maxTurns = 5;
	bool isRunning = false;
	bool isOutsideHouse = false;
	bool isFighting = false;

	std::string SafePlayerNames[10] =
	{
		"James",
		"Ethan",
		"Marcus",
		"Daniel",
		"Ryan",
		"Lucas",
		"Adrian",
		"Noah",
		"Jason",
		"Kevin"
	};

	Entity* SafePlayers[10] = { nullptr };
	int SafePlayerCount = 0;
	bool UsedNames[10] = { false };

	endings ending;
public:
	Game();
	void Run();

	int getTurns();
	void useTurn();
	//void randomScenario();
	//void randomSurvivor();
	//void randomSupply();
	void LookForSurvivors();
	static void clearConsole();
	void displayInventory();
	void displaySurvivors();
	void displayStatus();
	void displayLegend();
	void displayCurrentChunk();
	~Game();
};
