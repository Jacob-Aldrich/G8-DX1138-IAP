#include "Game.h"
#include "World.h"
#include "Object.h"
#include "Entity.h"
#include "Equipment.h"

Game::Game()
{
	world = new World(this);

	// SafePlayers includes the player as well as recruited survivors.
	SafePlayers[0] = player;
	SafePlayerCount = 1;

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

		std::cout << "\n";
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
			switch(randomAction) {
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
		if (insideInventoryMenu)
		{
			clearConsole();

			player->GetInventory().InventoryMenu();

			std::cout << "\n";
			std::cout << "[1] Select Item\n";
			std::cout << "[2] Store Equipped Item\n";
			std::cout << "[B] Exit\n";

			int keypress = _getch();

			if (keypress == 'b' || keypress == 'B')
			{
				insideInventoryMenu = false;
			}
			else if (keypress == '1')
			{
				int itemChoice;

				std::cout << "\nSelect item: ";
				std::cin >> itemChoice;

				itemChoice--;

				Object* selected =
					player->GetInventory().GetItem(itemChoice);

				if (selected != nullptr)
				{
					Equipment* equipment =
						dynamic_cast<Equipment*>(selected);

					if (equipment != nullptr)
					{
						player->GetInventory().EquipItem(itemChoice);
					}
					else
					{
						std::cout
							<< "This object cannot be equipped.\n";
					}
				}
			}

			else if (keypress == '2')
			{
				player->GetInventory().StoreEquippedItem();
			}

			continue;
		}

		if (insideHouseInventoryMenu)
		{
			clearConsole();

			std::cout << "INVENTORY MENU\n";
			std::cout << "---------------\n";

			std::cout << "Food Supply: "
				<< world->GetFood()->GetQuantity()
				<< "/"
				<< world->GetFood()->GetMaximumQuantity()
				<< "\n";

			std::cout << "Water Supply: "
				<< world->GetWater()->GetQuantity()
				<< "/"
				<< world->GetWater()->GetMaximumQuantity()
				<< "\n\n";

			std::cout << "Stored Items:\n";

			Inventory& inventory =
				player->GetInventory();

			if (inventory.GetItemCount() == 0)
			{
				std::cout << "[EMPTY]\n";
			}
			else
			{
				for (int i = 0;
					i < inventory.GetItemCount();
					i++)
				{
					Object* object =
						inventory.GetItem(i);

					if (object != nullptr)
					{
						std::cout << "["
							<< object->GetName()
							<< "] x1\n";
					}
				}
			}

			std::cout << "\nInventory Storage "
				<< inventory.GetItemCount()
				<< "/"
				<< inventory.GetMaximumItems()
				<< "\n";

			if (inventory.GetEquippedGear() != nullptr)
			{
				std::cout << "EQUIPPED ITEM: ["
					<< inventory.GetEquippedGear()->GetName()
					<< "]\n";
			}
			else
			{
				std::cout << "EQUIPPED ITEM: [NONE]\n";
			}

			std::cout << "\nPress 'b' to exit.\n";

			int keypress = _getch();

			if (keypress == 'b' || keypress == 'B')
			{
				insideHouseInventoryMenu = false;
			}

			continue;
		}

		if (Fighting) {
			clearConsole();
			std::cout << "You are in a fight!\n";
			std::cout << "Press 'f' to fight or 'r' to run away.\n";
			int keypress = _getch();
			world->HandleKeypress(keypress, dynamic_cast<Player*>(player));

			continue;
		}

		if (isOutsideHouse) {
			clearConsole();

			displayCurrentChunk();
			displayStatus();
			displayLegend();
			std::cout << "\nMove with W/A/S/D\nInteract with objects with E\n\n\nOpen/Close Inventory with B\n\n\n";

			world->GetChunks(world->getCurrentChunk()).PrintChunk(world->getCurrentChunk());
			world->displayInteractionOptions(dynamic_cast<Player*>(player));
			int keypress = _getch();
			world->HandleKeypress(keypress, dynamic_cast<Player*>(player));

			if (keypress == 'b' || keypress == 'B')
			{
				insideInventoryMenu = true;
			}
			continue;
		}

		clearConsole();
		std::cout << "Turns Remaining: " << Turns << "\n";
		std::cout << "Days Survived: " << world->getDays() << "\n";

		displayStatus();
		displayHouseWarnings();

		char choice;
		std::cout << "> What will you do?\n";
		std::cout << "[1] Eat Food\n";
		std::cout << "[2] Drink Water\n";
		std::cout << "[3] Open Inventory\n";
		std::cout << "[4] Go out of the house --THIS WILL SKIP ALL TURNS\n";
		std::cin >> choice;
		if (choice == '1')
		{
			EatFood();
		}
		else if (choice == '2')
		{
			DrinkWater();
		}
		else if (choice == '3')
		{
			insideHouseInventoryMenu = true;
		}
		else if (choice == '4')
		{
			std::cout << "Going out of the house\n";
			goOutsideHouse();
			Turns = 1;
			useTurn();
		}
		else
		{
			std::cout << "Invalid choice. Please choose again.\n";
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

	if (Turns <= 0)
	{
		Turns = maxTurns;
		world->addDays(1);

		// A new day means every person in the safe group, including
		// the player, becomes more hungry and thirsty.
		DecreaseSafePlayerNeeds();
	}
}

void Game::LookForSurvivors()
{
	// SafePlayers[0] is always the player, so there can be up to
	// three recruited survivors in addition to the player.
	if (SafePlayerCount < 4)
	{
		int RandomHP = rand() % 41 + 80;
		int RandomATK = rand() % 4 + 2;
		int RandomName = rand() % 10;

		while (UsedNames[RandomName] == true)
		{
			RandomName = rand() % 10;
		}

		UsedNames[RandomName] = true;

		SafePlayers[SafePlayerCount] = new Entity(
			SafePlayerNames[RandomName],
			RandomHP,
			RandomATK,
			false,
			'A'
		);

		std::string Name = SafePlayers[SafePlayerCount]->GetName();
		int Attack = SafePlayers[SafePlayerCount]->GetBaseAttackPoints();
		int HP = SafePlayers[SafePlayerCount]->GetHealthPoints();

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
	std::cout << "Food: " << world->GetFood()->GetQuantity() << "/" << world->GetFood()->GetMaximumQuantity() << "\n";
	std::cout << "Water: " << world->GetWater()->GetQuantity() << "/" << world->GetWater()->GetMaximumQuantity() << "\n";
}

void Game::displaySurvivors()
{
	for (int i = 0; i < SafePlayerCount; i++)
	{
		std::cout << "Safe Player " << i + 1 << ": "
			<< SafePlayers[i]->GetName() << "\n";
	}
}

void Game::displaySafePlayerNeeds()
{
	std::cout << "\nSafe Player Needs:\n";

	for (int i = 0; i < SafePlayerCount; i++)
	{
		if (SafePlayers[i] == nullptr)
		{
			continue;
		}

		std::cout << "[" << i + 1 << "] "
			<< SafePlayers[i]->GetName()
			<< " | Hunger: " << SafePlayers[i]->GetHunger() << "/100"
			<< " | Thirst: " << SafePlayers[i]->GetThirst() << "/100\n";
	}
}

void Game::displayHouseWarnings()
{
	for (int i = 0; i < SafePlayerCount; i++)
	{
		if (SafePlayers[i] == nullptr)
		{
			continue;
		}

		if (SafePlayers[i]->GetHunger() < 100)
		{
			std::cout << SafePlayers[i]->GetName() << " is hungry.\n";
		}

		if (SafePlayers[i]->GetThirst() < 100)
		{
			std::cout << SafePlayers[i]->GetName() << " is thirsty.\n";
		}
	}
}

void Game::DecreaseSafePlayerNeeds()
{
	for (int i = 0; i < SafePlayerCount; i++)
	{
		if (SafePlayers[i] == nullptr)
		{
			continue;
		}

		SafePlayers[i]->DecreaseHunger(DailyHungerLoss);
		SafePlayers[i]->DecreaseThirst(DailyThirstLoss);
	}
}

void Game::EatFood()
{
	if (world->GetFood()->IsEmpty())
	{
		std::cout << "There is no food available.\n";
		return;
	}

	displaySafePlayerNeeds();

	std::cout << "\nWho do you want to feed?\n";
	std::cout << "[0] Cancel\n";
	std::cout << "Select safe player: ";

	int choice;
	std::cin >> choice;

	if (choice == 0)
	{
		return;
	}

	if (choice < 1 || choice > SafePlayerCount ||
		SafePlayers[choice - 1] == nullptr)
	{
		std::cout << "Invalid safe player.\n";
		return;
	}

	Entity* target = SafePlayers[choice - 1];

	if (!world->GetFood()->UseQuantity(1))
	{
		std::cout << "There is no food available.\n";
		return;
	}

	target->IncreaseHunger(FoodRestoreAmount);

	std::cout << target->GetName() << " ate 1 food.\n";
	std::cout << "Hunger: " << target->GetHunger() << "/100\n";
	std::cout << "Food remaining: "
		<< world->GetFood()->GetQuantity() << "/"
		<< world->GetFood()->GetMaximumQuantity() << "\n";

	useTurn();
}

void Game::DrinkWater()
{
	if (world->GetWater()->IsEmpty())
	{
		std::cout << "There is no water available.\n";
		return;
	}

	displaySafePlayerNeeds();

	std::cout << "\nWho do you want to give water to?\n";
	std::cout << "[0] Cancel\n";
	std::cout << "Select safe player: ";

	int choice;
	std::cin >> choice;

	if (choice == 0)
	{
		return;
	}

	if (choice < 1 || choice > SafePlayerCount ||
		SafePlayers[choice - 1] == nullptr)
	{
		std::cout << "Invalid safe player.\n";
		return;
	}

	Entity* target = SafePlayers[choice - 1];

	if (!world->GetWater()->UseQuantity(1))
	{
		std::cout << "There is no water available.\n";
		return;
	}

	target->IncreaseThirst(WaterRestoreAmount);

	std::cout << target->GetName() << " drank 1 water.\n";
	std::cout << "Thirst: " << target->GetThirst() << "/100\n";
	std::cout << "Water remaining: "
		<< world->GetWater()->GetQuantity() << "/"
		<< world->GetWater()->GetMaximumQuantity() << "\n";

	useTurn();
}

void Game::displayStatus()
{
	displayInventory();
	displaySurvivors();

	std::cout << "Player Hunger: " << player->GetHunger() << "/100\n";
	std::cout << "Player Thirst: " << player->GetThirst() << "/100\n";
}

void Game::displayLegend()
{
	std::cout << "Legend:\n";
	std::cout << "P: Player | ";
	std::cout << "F: Food | ";
	std::cout << "W: Water | ";
	std::cout << "S: Sword | ";
	std::cout << "G: Gun | ";
	std::cout << "H: House | ";
}

void Game::displayCurrentChunk()
{
	std::cout << "You are at Chunk: " << world->getCurrentChunk() << "\n";
}

House* Game::getHouse()
{
	return house;
}

void Game::goOutsideHouse()
{
	isOutsideHouse = true;

	world->GetChunks(0).AddObject(player);
	player->SetX(5);
	player->SetY(6);

	world->GetChunks(0).AddObject(house);
	world->CreateObjects();
}

void Game::goInsideHouse()
{
	isOutsideHouse = false;

	Player* playerObject = dynamic_cast<Player*>(player);

	if (playerObject != nullptr)
	{
		playerObject->GetInventory().TransferSupplies(
			world->GetFood(),
			world->GetWater()
		);
	}

	world->GetChunks(world->getCurrentChunk()).RemoveObject(player);
	world->GetChunks(world->getCurrentChunk()).RemoveObject(house);

	world->DeleteAllObjects();
}

void Game::SetFighting(bool isFighting)
{
	Fighting = isFighting;
}

void Game::SetInsideInventoryMenu(bool isInsideInventoryMenu)
{
	insideInventoryMenu = isInsideInventoryMenu;
}

void Game::SetInsideHouseInventoryMenu(bool value)
{
	insideHouseInventoryMenu = value;
}
Game::~Game()
{
	// Player and House can be stored in World chunks while outside.
	// Remove them first so World does not delete them before Game does.
	if (isOutsideHouse)
	{
		world->GetChunks(world->getCurrentChunk()).RemoveObject(player);
		world->GetChunks(0).RemoveObject(house);
	}

	delete world;

	for (int i = 1; i < SafePlayerCount; i++)
	{
		delete SafePlayers[i];
		SafePlayers[i] = nullptr;
	}

	delete player;
	player = nullptr;

	delete house;
	house = nullptr;

	std::cout << "Destructing Game\n";
}