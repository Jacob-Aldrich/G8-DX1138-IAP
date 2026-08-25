#pragma once
#include "World.h"
#include "Entity.h"
#include "endings.h"
#include "Scenarios.h"
#include "Player.h"
#include <iostream>
#include <conio.h>
class Game
{
	World* world;
	int Turns;
	static int const maxTurns = 5;
	bool isRunning = false;
	bool isOutsideHouse = false;
	bool insideInventoryMenu = false;
	bool insideHouseInventoryMenu = false;
	bool Fighting = false;

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

	static const int DailyHungerLoss = 10;
	static const int DailyThirstLoss = 10;
	static const int FoodRestoreAmount = 25;
	static const int WaterRestoreAmount = 25;
	bool UsedNames[10] = { false };
	endings Endings;
	Scenarios scenarios;


	Player* player = new Player();
	House* house = new House('H', 5, 5, "House", this);
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
	void displaySafePlayerNeeds();
	void displayHouseWarnings();
	void EatFood();
	void DrinkWater();
	void DecreaseSafePlayerNeeds();
	void displayLegend();
	void displayCurrentChunk();

	House* getHouse();
	void goOutsideHouse();
	void goInsideHouse();
	
	void SetFighting(bool isFighting);
	void SetInsideInventoryMenu(bool isInsideInventoryMenu);
	void SetInsideHouseInventoryMenu(bool value);

	~Game();
};

