#include "Game.h"
#include "World.h"

Game::Game()
{
	world = new World;
	char choice;

	std::cout << "Constructing Game\n";
	std::cout << 
		R"(
You have 5 turns before nightfall.

Recruit survivors.
Gather food.
Find water.
Collect useful supplies.

Choose carefully.

Every person you save is another mouth
to feed.

And not everyone you meet is human.

Turns Remaining : 5

> What will you do?

[1] Search for supplies
[2] Look for survivors
[3] Return to the house --THIS WILL SKIP ALL TURNS
)";

	for (int i = 0; i < 5; i++) {
		std::cin >> choice;

		if (choice == '1') {
			std::cout << "Searching for supplies";
			
		}
		else if (choice == '2') {
			std::cout << "Looking for survivors";
			
		}
		else if (choice == '3') {
			std::cout << "Returning to the house";
			break;
		}
	}
}

void Game::Run()
{
	Turns = 5;


	while (true)
	{
		std::cin >> PlayerInput;

		switch (PlayerInput)
		{
		case 1:
			world->SearchForSupplies();
			break;

		case 2:
			LookForSurvivors();
			break;

		case 3:
			std::cout << "You went back to the house\n";
			return;

		default:
			std::cout << "Invalid input\n";
			break;
		}
	}
	
	std::cout << "Running Game\n";
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
	}
}

void Game::clearConsole()
{
	std::cout << "\033[H\033[2J";
}
void Game::CheckIfDead(Entity*& entity)
{
	if (entity->IsAlive() == false)
	{
		std::cout << entity->GetName() << " died and deleted\n";
		delete entity;
		entity = nullptr;
	}
}

void Game::LookForSurvivors()
{

	if (SafePlayerCount < 10)
	{
		int RandomName = rand() % 10;

		while (UsedNames[RandomName] == true)
		{
			RandomName = rand() % 10;
		}

		SafePlayers[SafePlayerCount] = new Entity(SafePlayerNames[RandomName], false);
		UsedNames[RandomName] = true;

		std::string Name = SafePlayers[SafePlayerCount]->GetName();
		int Attack = SafePlayers[SafePlayerCount]->GetBaseAttackPoints();
		int HP = SafePlayers[SafePlayerCount]->GetHealthPoints();

		std::cout << "You found " << Name << "!\n";
		std::cout << "Attack: " << Attack << "\n";
		std::cout << "HP:" << HP << "\n";

		SafePlayerCount++;
	}
	else
	{
		std::cout << "You cannot recruit any more survivors!\n";
	}
}

Game::~Game()
{
	delete world;
	std::cout << "Destructing Game\n";
}
