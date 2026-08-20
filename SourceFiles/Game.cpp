#include "Game.h"
#include "World.h"
#include "Object.h"
#include "Entity.h"

Game::Game()
{
	world = new World;
	char choice;

	std::cout << "Constructing Game\n";

	clearConsole();

	for (int i = 0; i < 5; i++) {
		std::cout << "You have 5 turns before nightfall.\n\n";

		std::cout << "Recruit survivors.\n";
		std::cout << "Gather food.\n";
		std::cout << "Find water.\n";
		std::cout << "Collect useful supplies.\n\n";

		std::cout << "Choose carefully.\n\n";

		std::cout << "Every person you save is another mouth\n";
		std::cout << "to feed.\n\n";

		std::cout << "And not everyone you meet is human.\n\n";

		std::cout << "Turns Remaining : " << 5 - i << "\n";

		displayStatus();

		std::cout << "> What will you do?\n\n";

		std::cout << "[1] Search for supplies\n";
		std::cout << "[2] Look for survivors\n";
		std::cout << "[3] Return to the house -- THIS WILL SKIP ALL TURNS\n";

		std::cin >> choice;

		if (choice == '1') {
			std::cout << "Searching for supplies\n";
			world->SearchForSupplies();
		}
		else if (choice == '2') {
			std::cout << "Looking for survivors\n";
			LookForSurvivors();
		}
		else if (choice == '3') {
			std::cout << "Returning to the house\n";
			break;
		}
		else {
			std::cout << "Invalid choice. Choosing Random Action.\n";

			int randomAction = rand() % 2 + 1;
			switch (randomAction) {
			case 1:
				std::cout << "Searching for supplies\n";
				world->SearchForSupplies();
				break;
			case 2:
				std::cout << "Looking for survivors\n";
				LookForSurvivors();
				break;
			}
		}
	}

	isRunning = true;
}

void Game::Run()
{
	Turns = 5;

	std::cout << "Running Game\n";

	while (isRunning) {
		if (isOutsideHouse) {
			clearConsole();

			displayCurrentChunk();
			displayStatus();
			displayLegend();
			std::cout << "\nMove with W/A/S/D\nInteract with objects with E\n\n\n";

			world->GetChunks(world->getCurrentChunk()).PrintChunk(world->getCurrentChunk());
			world->displayInteractionOptions();
			int keypress = _getch();
			world->HandleKeypress(keypress);
		}
		else {
			clearConsole();
			std::cout << "Turns Remaining: " << Turns << "\n";
			std::cout << "Days Survived: " << world->getDays() << "\n";

			displayStatus();

			char choice;
			std::cout << "> What will you do?\n";
			std::cout << "[1] Eat Food\n";
			std::cout << "[2] Drink Water\n";
			std::cout << "[3] Go out and Explore --THIS WILL SKIP ALL TURNS\n";
			std::cin >> choice;
			if (choice == '1') {
				std::cout << "Eating...\n";
				useTurn();
			}
			else if (choice == '2') {
				std::cout << "Drinking...\n";
				useTurn();
			}
			else if (choice == '3') {
				std::cout << "Going out of the house\n";
				isOutsideHouse = true;
			}
			else {
				std::cout << "Invalid choice. Please choose again.\n";
			}
		}
	}
}


int Game::getTurns()
{
	return Turns;
}

void Game::useTurn()
{
	Turns--;
	if (Turns <= 0) {
		Turns = maxTurns;
		world->addDays(1);
	}
}

void Game::LookForSurvivors()
{
	if (SafePlayerCount < 3)
	{
		int RandomHP = rand() % 41 + 80;
		int RandomATK = rand() % 4 + 2;
		int RandomName = rand() % 10;

		while (UsedNames[RandomName] == true)
		{
			RandomName = rand() % 10;
		}

		UsedNames[RandomName] = true;

		SafePlayers[RandomName] = new Entity(
			SafePlayerNames[RandomName],
			RandomHP,
			RandomATK,
			false,
			'A'
		);

		std::string Name = SafePlayers[RandomName]->GetName();
		int Attack = SafePlayers[RandomName]->GetBaseAttackPoints();
		int HP = SafePlayers[RandomName]->GetHealthPoints();

		std::cout << "You found " << Name << "!\n";
		std::cout << "Attack: " << Attack << "\n";
		std::cout << "HP: " << HP << "\n";

		SafePlayerCount++;
	}
	else
	{
		std::cout << "You cannot recruit any more survivors!\n";
	}
}

void Game::clearConsole()
{
	std::cout << "\033[H\033[2J";
}

void Game::displayInventory()
{
	std::cout << "\nStorage:\n";
	std::cout << "Food: " << world->GetFood()->GetQuantity() << "/" << world->GetFood()->GetMaximumQuantity() << "\n";
	std::cout << "Water: " << world->GetWater()->GetQuantity() << "/" << world->GetWater()->GetMaximumQuantity() << "\n\n";
}

void Game::displaySurvivors()
{
	for (int i = 0; i < SafePlayerCount; i++)
	{
		std::cout << "Survivor " << i + 1 << ": " << SafePlayers[i]->GetName() << "\n";
	}
}

void Game::displayStatus()
{
	displayInventory();
	displaySurvivors();
}

void Game::displayLegend()
{
	std::cout << "Legend:\n";
	std::cout << "P: Player\n";
	std::cout << "F: Food\n";
	std::cout << "W: Water\n";
	std::cout << "H: House\n";
}

void Game::displayCurrentChunk()
{
	std::cout << "You are at Chunk: " << world->getCurrentChunk() << "\n";
}

Game::~Game()
{
	delete world;
	std::cout << "Destructing Game\n";
}