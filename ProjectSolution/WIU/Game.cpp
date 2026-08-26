#include "Game.h"
#include "World.h"
#include "Object.h"
#include "Entity.h"
#include "Equipment.h"
#include "ConsoleColors.h"
#include "skinwalker.h"

//junlong
Game::Game()
{
    world = new World(this);

    SafePlayers[0] = player;
    SafePlayerCount = 1;

    char choice;

    std::cout << "Constructing Game\n";
    clearConsole();

    for (int i = 0; i < 5; i++)
    {
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
        displaySurvivors();
        std::cout << "> What will you do?\n\n";
        std::cout << "[1] Search for supplies\n";
        std::cout << "[2] Look for survivors\n";
        std::cout << "[3] Return to the house -- THIS WILL SKIP ALL TURNS\n";
        std::cin >> choice;

        if (choice == '1')
        {
            std::cout << "Searching for supplies\n";
            world->SearchForSupplies();
        }
        else if (choice == '2')
        {
            std::cout << "Looking for survivors\n";
            LookForSurvivors();
        }
        else if (choice == '3')
        {
            std::cout << "Returning to the house\n";
            break;
        }
        else
        {
            std::cout << "Invalid choice. Choosing Random Action.\n";
            int randomAction = rand() % 2 + 1;
            if (randomAction == 1)
            {
                world->SearchForSupplies();
            }
            else
            {
                LookForSurvivors();
            }
        }
    }

    isRunning = true;
}

//junlong
void Game::Run()
{
    Turns = 5;

    while (isRunning)
    {
        if (!player->IsAlive())
        {
            CheckForPlayerDeath();
            break;
        }

        if (insideInventoryMenu)
        {
            clearConsole();
            player->GetInventory().InventoryMenu();
            std::cout << "\n[1] Select Item\n";
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

                Object* selected = player->GetInventory().GetItem(itemChoice);
                if (selected != nullptr)
                {
                    Equipment* equipment = dynamic_cast<Equipment*>(selected);
                    if (equipment != nullptr)
                    {
                        player->GetInventory().EquipItem(itemChoice);
                    }
                    else
                    {
                        std::cout << "This object cannot be equipped.\n";
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
            std::cout << "INVENTORY MENU\n---------------\n";
            std::cout << "Food Supply: " << world->GetFood()->GetQuantity()
                      << "/" << world->GetFood()->GetMaximumQuantity() << "\n";
            std::cout << "Water Supply: " << world->GetWater()->GetQuantity()
                      << "/" << world->GetWater()->GetMaximumQuantity() << "\n\n";

            Inventory& inventory = player->GetInventory();
            std::cout << "Stored Items:\n";
            if (inventory.GetItemCount() == 0)
            {
                std::cout << "[EMPTY]\n";
            }
            else
            {
                for (int i = 0; i < inventory.GetItemCount(); i++)
                {
                    Object* object = inventory.GetItem(i);
                    if (object != nullptr)
                    {
                        std::cout << "[" << i + 1 << "] " << object->GetName() << " x1\n";
                    }
                }
            }

            std::cout << "\nStorage " << inventory.GetItemCount()
                      << "/" << inventory.GetMaximumItems() << "\n";
            DisplayEquipmentFor(player);
            for (int i = 1; i < SafePlayerCount; i++)
            {
                DisplayEquipmentFor(SafePlayers[i]);
            }

            std::cout << "\n[1] Equip stored item to a safe player\n";
            std::cout << "[B] Exit\n";
            int keypress = _getch();

            if (keypress == 'b' || keypress == 'B')
            {
                insideHouseInventoryMenu = false;
            }
            else if (keypress == '1')
            {
                EquipStoredItemToSafePlayer();
            }
            continue;
        }

        if (Fighting)
        {
            // Combat is fully handled when the encounter starts.
            Fighting = false;
            continue;
        }

        if (isOutsideHouse)
        {
            clearConsole();
            displayCurrentChunk();
            displayLegend();
            displayPartyStatus();
            
            std::cout << "\nMove with W/A/S/D\nInteract with objects with E\n";
            std::cout << "Open/Close Inventory with B\n\n";
            world->GetChunks(world->getCurrentChunk()).PrintChunk(world->getCurrentChunk());
            world->displayInteractionOptions(player);

            int keypress = _getch();
            world->HandleKeypress(keypress, player);

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
        std::cout << "\n> What will you do?\n";
        std::cout << "[1] Eat Food\n";
        std::cout << "[2] Drink Water\n";
        std::cout << "[3] Open Inventory\n";
        std::cout << "[4] Go out of the house -- THIS WILL SKIP ALL TURNS\n";
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
            goOutsideHouse();
        }
        //else if (choice == '4')
        //{
        //    goOutsideHouse();
        //    Turns = 1;
        //    useTurn();
        //}
        else
        {
            std::cout << "Invalid choice. Please choose again.\n";
        }
    }
}

int Game::getTurns() { return Turns; }

// jacob
void Game::useTurn()
{
    Turns--;

    if (Turns <= 0)
    {
        Turns = maxTurns;
        world->addDays(1);

        // Hunger, thirst and starvation damage happen first.
        DecreaseSafePlayerNeeds();

        // Dead players cannot recover health or win.
        if (player != nullptr && player->IsAlive())
        {
            RecoverPlayerHealthForNewDay();
            CheckForCarAppearance();
            CheckForHelicopterArrival();
        }

        if (!isRunning || player == nullptr || !player->IsAlive())
        {
            return;
        }
    }

    if (!isOutsideHouse && isRunning && player != nullptr && player->IsAlive())

    {
        scenarios.ChooseRandomEvent(this);
    }
}
void Game::RecoverPlayerHealthForNewDay()
{
    // SafePlayers[0] is the main player.
    // SafePlayers[1] onward are recruited survivors.
    for (int i = 0; i < SafePlayerCount; i++)
    {
        Entity* person = SafePlayers[i];

        if (person == nullptr || !person->IsAlive())
        {
            continue;
        }

        int maximumHealth = person->GetMaximumHealthPoints();
        int healingAmount = maximumHealth * DailyHealthRecoveryPercentage / 100;
        int healthBefore = person->GetHealthPoints();
        person->RestoreHealth(healingAmount);

        int healthRecovered = person->GetHealthPoints() - healthBefore;

        if (healthRecovered > 0)
        {
            std::cout
                << person->GetName()
                << " recovered "
                << healthRecovered
                << " HP.\n";
        }
    }
}

void Game::CheckForCarAppearance()
{
    // the car cannot appear before day 3
    if (world->getDays() < CarUnlockDay)
    {
        return;
    }

    // dont create another car if one is already there
    // or if the helicopter has already been called.
    if (carAvailable || helicopterCalled)
    {
        return;
    }

    if (rand() % 100 < CarAppearanceChance)
    {
        carAvailable = true;
        ConsoleColor::Print("\nA car has appeared somewhere outside!\n", ConsoleColor::BRIGHT_GREEN);
    }
}

bool Game::IsCarAvailable()
{
    return carAvailable && !helicopterCalled;
}

void Game::CallHelicopter()
{
    if (helicopterCalled)
    {
        std::cout
            << "The helicopter has already been called.\n"
            << "You must survive until it arrives.\n";
        return;
    }

    helicopterCalled = true;
    carAvailable = false;
    helicopterCallDay = world->getDays();

    ConsoleColor::Print("\nYou activate the car's emergency radio!\n", ConsoleColor::BRIGHT_GREEN);

    std::cout
        << "A helicopter received your signal.\n"
        << "It will arrive after you survive "
        << HelicopterArrivalDelay
        << " more days.\n";
}

void Game::CheckForHelicopterArrival()
{
    if (!helicopterCalled || player == nullptr || !player->IsAlive())
    {
        return;
    }

    int daysSinceCall = world->getDays() - helicopterCallDay;

    if (daysSinceCall >= HelicopterArrivalDelay)
    {
        int survivorsAlive = 0;
        for (int i = 1; i < SafePlayerCount; i++)
        {
            if (SafePlayers[i] != nullptr && SafePlayers[i]->IsAlive())
            {
                survivorsAlive++;
            }
        }

        int daysSurvived = 0;
        if (world != nullptr)
        {
            daysSurvived = world->getDays();
        }
        else
        {
            daysSurvived = 0;
        }

        Endings.HelicopterEnding(daysSurvived, survivorsAlive);
        isRunning = false;
    }
}

// junlong
//void Game::useTurn()
//{
//    Turns--;
//
//    if (Turns <= 0)
//    {
//        Turns = maxTurns;
//        world->addDays(1);
//        DecreaseSafePlayerNeeds();
//    }
//
//    // House scenarios are checked after every completed turn, but never
//    // after going outside because isOutsideHouse has already been set true.
//    if (!isOutsideHouse && isRunning && player != nullptr && player->IsAlive())
//    {
//        scenarios.ChooseRandomEvent(this);
//    }
//}

//junlong
void Game::LookForSurvivors()
{
    if (SafePlayerCount < maxSafePlayers)
    {
        int RandomHP = rand() % 41 + 80;
        int RandomATK = rand() % 4 + 2;
        int RandomName = rand() % 10;
        while (UsedNames[RandomName])
        {
            RandomName = rand() % 10;
        }

        UsedNames[RandomName] = true;
        SafePlayers[SafePlayerCount] = new Entity(SafePlayerNames[RandomName], RandomHP, RandomATK, false, 'A');

        std::cout << "You found " << SafePlayers[SafePlayerCount]->GetName() << "!\n";
        std::cout << "Attack: " << SafePlayers[SafePlayerCount]->GetBaseAttackPoints() << "\n";
        std::cout << "HP: " << SafePlayers[SafePlayerCount]->GetHealthPoints() << "\n";
        SafePlayerCount++;
    }
    else {
        std::cout << "You cannot recruit any more survivors!\n";
    }   
}

void Game::clearConsole() { std::cout << "\033[H\033[2J"; }

void Game::displayInventory()
{
    ConsoleColor::Print("Food: ", ConsoleColor::BRIGHT_YELLOW);
    std::cout << world->GetFood()->GetQuantity() << "/" << world->GetFood()->GetMaximumQuantity() << "\n";
    ConsoleColor::Print("Water: ", ConsoleColor::BRIGHT_BLUE);
    std::cout << world->GetWater()->GetQuantity() << "/" << world->GetWater()->GetMaximumQuantity() << "\n";
}

void Game::displaySurvivors()
{
    std::cout << '\n';
    for (int i = 0; i < SafePlayerCount; i++)
    {
        if (SafePlayers[i] == nullptr) 
        { 
            continue; 
        }
        std::cout << "Survivor " << i + 1 << ": " << SafePlayers[i]->GetName()
                  << " | HP: " << SafePlayers[i]->GetHealthPoints()
                  << " | Base ATK: " << SafePlayers[i]->GetBaseAttackPoints()
                  << " | Hunger: " << SafePlayers[i]->GetHunger()
                  << " | Thirst: " << SafePlayers[i]->GetThirst() << "\n";
    }
    std::cout << '\n';
}

void Game::displaySafePlayerNeeds()
{
    std::cout << "\nSafe Player Needs:\n";
    for (int i = 0; i < SafePlayerCount; i++)
    {
        if (SafePlayers[i] == nullptr || !SafePlayers[i]->IsAlive())
        {
            continue;
        }
        std::cout << "[" << i + 1 << "] " << SafePlayers[i]->GetName()
                  << " | Hunger: " << SafePlayers[i]->GetHunger() << "/100"
                  << " | Thirst: " << SafePlayers[i]->GetThirst() << "/100\n";
    }
}
//junlong
void Game::displayHouseWarnings()
{
    std::cout << "Door durability: " << house->GetDoorDurability()
              << "/" << house->GetMaximumDoorDurability() << "\n";

    if (house->IsDoorBroken())
    {
        ConsoleColor::Print("WARNING: THE FRONT DOOR IS BROKEN.\n", ConsoleColor::BRIGHT_RED);
    }
    else if (house->GetDoorDurability() <= 40)
    {
        ConsoleColor::Print("WARNING: The front door badly needs repairs.\n", ConsoleColor::YELLOW);
    }

    for (int i = 0; i < SafePlayerCount; i++)
    {
        if (SafePlayers[i] == nullptr || !SafePlayers[i]->IsAlive())
        {
            continue;
        }

        if (SafePlayers[i]->GetHunger() < 50)
        {
            ConsoleColor::Print(SafePlayers[i]->GetName() + " is hungry.\n", ConsoleColor::YELLOW);
        }

        if (SafePlayers[i]->GetThirst() < 50)
        {
            ConsoleColor::Print(SafePlayers[i]->GetName() + " is thirsty.\n", ConsoleColor::BRIGHT_BLUE);
        }
    }
}

void Game::DecreaseSafePlayerNeeds()
{
    for (int i = 0; i < SafePlayerCount; i++)
    {
        if (SafePlayers[i] == nullptr || !SafePlayers[i]->IsAlive()) 
        { 
            continue; 
        }
        SafePlayers[i]->DecreaseHunger(DailyHungerLoss);
        SafePlayers[i]->DecreaseThirst(DailyThirstLoss);

        Entity* person = SafePlayers[i];

        if (person->GetHunger() <= 0 || person->GetThirst() <= 0) {
            person->TakeDamage(25);
        }

        if (person == player && !player->IsAlive())
        {
            CheckForPlayerDeath();
        }
        else if (person != player && !person->IsAlive())
        {
            RemoveDeadSurvivor(person);
            i--;
        }
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
    bool fed[10] = { false };
    bool fedAnyone = false;

    while (!world->GetFood()->IsEmpty())
    {
        std::cout << "\nWho do you want to feed? (0 = done)\n";
        int choice;
        std::cin >> choice;
        if (choice == 0)
        {
            break;
        }
        if (choice < 1 || choice > SafePlayerCount || SafePlayers[choice - 1] == nullptr || !SafePlayers[choice - 1]->IsAlive())
        {
            std::cout << "Invalid safe player.\n";
            continue;
        }
        if (fed[choice - 1])
        {
            std::cout << "That person has already been fed during this action.\n";
            continue;
        }

        Entity* target = SafePlayers[choice - 1];
        world->GetFood()->UseQuantity(1);
        target->IncreaseHunger(FoodRestoreAmount);
        fed[choice - 1] = true;
        fedAnyone = true;
        std::cout << target->GetName() << " ate 1 food. Hunger: " << target->GetHunger() << "/100\n";
        std::cout << "Food remaining: " << world->GetFood()->GetQuantity() << "\n";
    }

    if (fedAnyone)
    {
        useTurn();
    }
}

void Game::DrinkWater()
{
    if (world->GetWater()->IsEmpty())
    {
        std::cout << "There is no water available.\n";
        return;
    }

    displaySafePlayerNeeds();
    bool drank[10] = { false };
    bool drankAnyone = false;

    while (!world->GetWater()->IsEmpty())
    {
        std::cout << "\nWho do you want to give water to? (0 = done)\n";
        int choice;
        std::cin >> choice;
        if (choice == 0)
        {
            break;
        }
        if (choice < 1 || choice > SafePlayerCount || SafePlayers[choice - 1] == nullptr || !SafePlayers[choice - 1]->IsAlive())
        {
            std::cout << "Invalid safe player.\n";
            continue;
        }
        if (drank[choice - 1])
        {
            std::cout << "That person has already received water during this action.\n";
            continue;
        }

        Entity* target = SafePlayers[choice - 1];
        world->GetWater()->UseQuantity(1);
        target->IncreaseThirst(WaterRestoreAmount);
        drank[choice - 1] = true;
        drankAnyone = true;
        std::cout << target->GetName() << " drank 1 water. Thirst: " << target->GetThirst() << "/100\n";
        std::cout << "Water remaining: " << world->GetWater()->GetQuantity() << "\n";
    }

    if (drankAnyone)
    {
        useTurn();
    }
}

void Game::displayStatus()
{
    displayInventory();
    displaySurvivors();
    std::cout << "Player HP: " << player->GetHealthPoints() << "/" << player->GetMaximumHealthPoints() << "\n";

    if (carAvailable && !helicopterCalled)
    {
        ConsoleColor::Print("A car is somewhere outside.\n", ConsoleColor::BRIGHT_GREEN);
    }

    if (helicopterCalled)
    {
        int daysPassed = world->getDays() - helicopterCallDay;
        int daysRemaining = HelicopterArrivalDelay - daysPassed;

        if (daysRemaining < 0)
        {
            daysRemaining = 0;
        }

        ConsoleColor::Print("Helicopter arrival: ", ConsoleColor::BRIGHT_GREEN);
        std::cout << daysRemaining << " day(s) remaining.\n";
    }
}
//junlong
void Game::displayLegend()
{
    std::cout << "Legend:\n";
    ConsoleColor::PrintSymbol('P');
    std::cout << ": Player | ";
    ConsoleColor::PrintSymbol('F');
    std::cout << ": Food | ";
    ConsoleColor::PrintSymbol('W');
    std::cout << ": Water | ";
    ConsoleColor::PrintSymbol('S');
    std::cout << ": Sword | ";
    ConsoleColor::PrintSymbol('G');
    std::cout << ": Gun | ";
    ConsoleColor::PrintSymbol('H');
    std::cout << ": House |";
    ConsoleColor::PrintSymbol('C');
    std::cout << ": Car\n";
}

void Game::displayCurrentChunk()
{
    std::cout << "You are at Chunk: " << world->getCurrentChunk() << "\n";
}

void Game::displayPartyStatus()
{
    std::cout << "\nParty Members:\n";

	for (int i = 0; i < ActivePartyCount; i++)
	{
		if (ActiveParty[i] == nullptr || !ActiveParty[i]->IsAlive())
		{
			continue;
		}

		std::cout << "[" << i + 1 << "] " << ActiveParty[i]->GetName()
			<< " | HP: " << ActiveParty[i]->GetHealthPoints() << "/" << ActiveParty[i]->GetMaximumHealthPoints()
			<< " | Hunger: " << ActiveParty[i]->GetHunger() << "/100"
			<< " | Thirst: " << ActiveParty[i]->GetThirst() << "/100\n";
	}
}

House* Game::getHouse() { 
    return house; 
}

void Game::ChooseOutsideParty()
{
    clearConsole();
    ActiveParty[0] = player;
    ActivePartyCount = 1;

    if (SafePlayerCount <= 1)
    {
        player->GetInventory().SetCapacityBonus(0);
        return;
    }

    std::cout << "\nChoose who to bring outside. Player is always included.\n";
    std::cout << "You can bring up to TWO companions.\n";
    std::cout << "Enter the NUMBER beside a survivor's name, not their name.\n";
    std::cout << "Enter 0 when you are finished choosing.\n\n";
    displaySurvivors();

    bool chosen[10] = { false };
    int selected = 0;
    while (selected < 2)
    {
        std::cout << "Choose a survivor by number (0 = done): ";
        int choice;
        std::cin >> choice;
        if (choice == 0)
        {
            break;
        }
        if (choice < 2 || choice > SafePlayerCount || SafePlayers[choice - 1] == nullptr || !SafePlayers[choice - 1]->IsAlive())
        {
            std::cout << "Invalid survivor.\n";
            continue;
        }
        if (chosen[choice - 1])
        {
            std::cout << "That survivor is already selected.\n";
            continue;
        }

        chosen[choice - 1] = true;
        ActiveParty[ActivePartyCount++] = SafePlayers[choice - 1];
        selected++;
    }

    player->GetInventory().SetCapacityBonus(selected * OutsideStoragePerCompanion);
    std::cout << "Outside storage: " << player->GetInventory().GetMaximumItems() << " items.\n";
}

//jacob
void Game::goOutsideHouse()
{
    // Mark the player as outside before completing the day.
    // This prevents a house scenario from happening during departure.
    isOutsideHouse = true;

    // Going outside skips all remaining turns.
    Turns = 1;
    useTurn();

    if (!isRunning || player == nullptr || !player->IsAlive())
    {
        isOutsideHouse = false;
        return;
    }

    ChooseOutsideParty();

    world->GetChunks(0).AddObject(player);
    player->SetX(5);
    player->SetY(6);

    world->GetChunks(0).AddObject(house);
    world->CreateObjects();
}

//junlong
//void Game::goOutsideHouse()
//{
//    ChooseOutsideParty();
//    isOutsideHouse = true;
//
//    world->GetChunks(0).AddObject(player);
//    player->SetX(5);
//    player->SetY(6);
//    world->GetChunks(0).AddObject(house);
//    world->CreateObjects();
//}

//junlong
void Game::goInsideHouse()
{
    // Combat is synchronous, so normally there should be no active combat
    // when the house is entered. Clear the state defensively in case the
    // house is reached immediately after an encounter.
    Fighting = false;
    isOutsideHouse = false;

    player->GetInventory().TransferSupplies(world->GetFood(), world->GetWater());
    player->GetInventory().SetCapacityBonus(0);

    // Player and house are owned by Game, not World. Remove them from the
    // chunk before cleaning up outdoor objects so they are never deleted
    // and left as dangling pointers.
    world->GetChunks(world->getCurrentChunk()).RemoveObject(player);
    world->GetChunks(world->getCurrentChunk()).RemoveObject(house);
    world->DeleteAllObjects();

    for (int i = 0; i < 3; i++)
    {
        ActiveParty[i] = nullptr;
    }
    ActivePartyCount = 0;
}
//junlong
void Game::SetFighting(bool isFighting) { 
    Fighting = isFighting; 
}
//junlong
void Game::SetInsideInventoryMenu(bool value) { 
    insideInventoryMenu = value; 
}
//junlong
void Game::SetInsideHouseInventoryMenu(bool value) {
    insideHouseInventoryMenu = value; 
}

//junlong
bool Game::IsInActiveParty(Entity* entity)
{
    for (int i = 0; i < ActivePartyCount; i++)
    {
        if (ActiveParty[i] == entity)
        {
            return true;
        }
    }
    return false;
}
//junlong

Equipment* Game::GetCombatEquipment(Entity* entity)
{
    if (entity == player)
    {
        return player->GetInventory().GetEquippedGear();
    }
    return entity->GetEquippedGear();
}

// junlong
int Game::GetCombatAttack(Entity* entity)
{
    Equipment* gear = GetCombatEquipment(entity);
    int base = entity->GetBaseAttackPoints();
    if (gear == nullptr)
    {
        return base;
    }

    if (gear->DoesSetAttackExactly())
    {
        return gear->GetAttackValue();
    }

    if (gear->IsInstantDefeatGear())
    {
        return base;
    }

    return base + gear->GetAttackValue();
}

// junlong
int Game::CalculateCombatDamage(Entity* attacker, Entity* defender, bool& veryEffective, bool& notEffective)
{
    veryEffective = false;
    notEffective = false;

    Equipment* gear = GetCombatEquipment(attacker);
    double multiplier = 1.0;

    if (gear != nullptr)
    {
        if (gear->GetType() == ItemType::GUN && defender->GetIsSkinWalker())
        {
            multiplier = 1.5;
        }
        else if (gear->GetType() == ItemType::SWORD && defender->GetIsSkinWalker())
        {
            multiplier = 0.75;
        }
    }

    // Small random damage variation keeps combat from being identical.
    double randomMultiplier = (rand() % 21 + 90) / 100.0;
    int damage = static_cast<int>(GetCombatAttack(attacker) * multiplier * randomMultiplier);
    if (damage < 1)
    {
        damage = 1;
    }

    if (multiplier >= 1.4)
    {
        veryEffective = true;
    }
    if (multiplier <= 0.75)
    {
        notEffective = true;
    }

    return damage;
}

//junlong
void Game::RemoveDefeatedEnemy(int enemyIndex)
{
    if (enemyIndex < 0 || enemyIndex >= EnemyCount)
    {
        return;
    }

    delete Enemies[enemyIndex];
    Enemies[enemyIndex] = nullptr;

    for (int i = enemyIndex; i < EnemyCount - 1; i++)
    {
        Enemies[i] = Enemies[i + 1];
        EnemyDefending[i] = EnemyDefending[i + 1];
    }

    Enemies[EnemyCount - 1] = nullptr;
    EnemyDefending[EnemyCount - 1] = false;
    EnemyCount--;
}

//junlong
void Game::DisplayCombatStatus()
{
    std::cout << "\n========== BATTLE ==========" << "\n";
    std::cout << "YOUR PARTY\n";
    for (int i = 0; i < ActivePartyCount; i++)
    {
        Entity* p = ActiveParty[i];
        std::cout << "[" << i + 1 << "] " << p->GetName()
                  << " HP " << p->GetHealthPoints()
                  << " ATK " << GetCombatAttack(p);
        Equipment* gear = GetCombatEquipment(p);
        if (gear != nullptr)
        {
            std::cout << " [" << gear->GetName() << "]";
        }
        std::cout << "\n";
    }

    std::cout << "\nENEMIES\n";
    for (int i = 0; i < EnemyCount; i++)
    {
        if (Enemies[i] == nullptr)
        {
            continue;
        }
        std::cout << "[" << i + 1 << "] " << Enemies[i]->GetName()
                  << " HP " << Enemies[i]->GetHealthPoints()
                  << " ATK " << Enemies[i]->GetBaseAttackPoints() << "\n";
    }
    std::cout << "============================\n";
}

//junlong
void Game::PlayerCombatTurn(int partyIndex)
{
    Entity* attacker = ActiveParty[partyIndex];
    if (!attacker->IsAlive()) { return; }

    while (true)
    {
        DisplayCombatStatus();
        std::cout << "\n" << attacker->GetName() << "'s turn!\n";
        std::cout << "[1] Attack\n[2] Defend\n> ";
        char choice;
        std::cin >> choice;

        if (choice == '2')
        {
            Defending[partyIndex] = true;
            std::cout << attacker->GetName() << " is defending!\n";
            return;
        }
        if (choice != '1')
        {
            std::cout << "Invalid choice.\n";
            continue;
        }

        int targetChoice;
        std::cout << "Choose enemy: ";
        std::cin >> targetChoice;
        targetChoice--;
        if (targetChoice < 0 || targetChoice >= EnemyCount || Enemies[targetChoice] == nullptr || !Enemies[targetChoice]->IsAlive())
        {
            std::cout << "Invalid enemy.\n";
            continue;
        }

        Equipment* gear = GetCombatEquipment(attacker);
        if (gear != nullptr && gear->IsInstantDefeatGear() && gear->HasUsesRemaining())
        {
            gear->UseOnce();
            Enemies[targetChoice]->TakeDamage(Enemies[targetChoice]->GetHealthPoints());
            std::cout << "\n" << attacker->GetName() << " used " << gear->GetName() << "!\n";
            std::cout << "VERY EFFICIENT! INSTANT DEFEAT!\n";
            std::cout << gear->GetUsesRemaining() << " uses remaining.\n";
            return;
        }

        bool veryEffective, notEffective;
        int damage = CalculateCombatDamage(attacker, Enemies[targetChoice], veryEffective, notEffective);
        if (EnemyDefending[targetChoice])
        {
            damage = (damage + 1) / 2;
            EnemyDefending[targetChoice] = false;
            std::cout << Enemies[targetChoice]->GetName() << " blocks part of the attack!\n";
        }
        Enemies[targetChoice]->TakeDamage(damage);
        std::cout << "\n" << attacker->GetName() << " attacks " << Enemies[targetChoice]->GetName()
                  << " for " << damage << " damage!\n";
        if (veryEffective) { std::cout << "VERY EFFICIENT!\n"; }
        else if (notEffective) { std::cout << "NOT EFFICIENT\n"; }
        if (!Enemies[targetChoice]->IsAlive())
        {
            std::cout << Enemies[targetChoice]->GetName() << " was defeated!\n";
            RemoveDefeatedEnemy(targetChoice);
        }
        return;
    }
}

//junlong
void Game::SurvivorCombatTurn(int partyIndex)
{
    Entity* attacker = ActiveParty[partyIndex];
    if (!attacker->IsAlive())
    {
        return;
    }

    // Simple party AI: usually attack, sometimes defend.
    if (rand() % 5 == 0)
    {
        Defending[partyIndex] = true;
        std::cout << attacker->GetName() << " braces for the next attack!\n";
        return;
    }

    int target = -1;
    int lowestHP = 100000;
    for (int i = 0; i < EnemyCount; i++)
    {
        if (Enemies[i] != nullptr && Enemies[i]->IsAlive() && Enemies[i]->GetHealthPoints() < lowestHP)
        {
            lowestHP = Enemies[i]->GetHealthPoints();
            target = i;
        }
    }
    if (target < 0) { return; }

    Equipment* gear = GetCombatEquipment(attacker);
    if (gear != nullptr && gear->IsInstantDefeatGear() && gear->HasUsesRemaining())
    {
        gear->UseOnce();
        Enemies[target]->TakeDamage(Enemies[target]->GetHealthPoints());
        std::cout << attacker->GetName() << " used " << gear->GetName() << " and instantly defeated " << Enemies[target]->GetName() << "!\n";
        RemoveDefeatedEnemy(target);
        return;
    }

    bool veryEffective, notEffective;
    int damage = CalculateCombatDamage(attacker, Enemies[target], veryEffective, notEffective);
    if (EnemyDefending[target])
    {
        damage = (damage + 1) / 2;
        EnemyDefending[target] = false;
        std::cout << Enemies[target]->GetName() << " blocks part of the attack!\n";
    }
    Enemies[target]->TakeDamage(damage);
    std::cout << attacker->GetName() << " attacks " << Enemies[target]->GetName() << " for " << damage << " damage!\n";
    if (veryEffective) 
    { std::cout << "VERY EFFICIENT!\n"; }
    else if (notEffective) 
    { std::cout << "NOT EFFICIENT\n"; }

    if (!Enemies[target]->IsAlive())
    {
        std::cout << Enemies[target]->GetName() << " was defeated!\n";
        RemoveDefeatedEnemy(target);
    }
}

//junlong
void Game::EnemyCombatTurn(int enemyIndex)
{
    Entity* enemy = Enemies[enemyIndex];
    if (enemy == nullptr || !enemy->IsAlive())
    {
        return;
    }

    int living[3];
    int count = 0;
    for (int i = 0; i < ActivePartyCount; i++)
    {
        if (ActiveParty[i] != nullptr && ActiveParty[i]->IsAlive()) { living[count++] = i; }
    }
    if (count == 0)
    {
        return;
    }

    // Enemies also get an attack/defend choice, like the player's party.
    if (rand() % 5 == 0)
    {
        EnemyDefending[enemyIndex] = true;
        std::cout << enemy->GetName() << " is defending!\n";
        return;
    }

    int targetIndex = living[rand() % count];
    Entity* target = ActiveParty[targetIndex];
    int damage = enemy->GetBaseAttackPoints() + rand() % 4;

    if (Defending[targetIndex])
    {
        damage = (damage + 1) / 2;
        std::cout << target->GetName() << " blocks part of the attack!\n";
        Defending[targetIndex] = false;
    }

    target->TakeDamage(damage);
    std::cout << enemy->GetName() << " attacks " << target->GetName()
              << " for " << damage << " damage!\n";

    if (!target->IsAlive())
    {
        std::string deadName = target->GetName();
        std::cout << deadName << " has fallen!\n";
        if (target == player)
        {
            CheckForPlayerDeath();
        }
        else
        {
            RemoveDeadSurvivor(target);
        }
    }
}

//junlong
void Game::TriggerCombatScenario()
{
    // 75% chance each combat round.
    if (rand() % 100 >= 75)
    {
        return;
    }

    int type = rand() % 4;
    std::cout << "\n--- SCENARIO ---\n";

    if (type == 0)
    {
        // SEND_SOMEONE_EVENT: one living companion takes a hit to protect the group.
        int candidates[3], count = 0;
        for (int i = 1; i < ActivePartyCount; i++)
        {
            if (ActiveParty[i]->IsAlive()) { candidates[count++] = i; }
        }

        if (count > 0)
        {
            Entity* target = ActiveParty[candidates[rand() % count]];
            int damage = 5 + rand() % 8;
            target->TakeDamage(damage);
            std::cout << target->GetName() << " steps in front of an attack and takes " << damage << " damage!\n";
        }
        else
        {
            std::cout << "You hear something moving in the darkness...\n";
        }
    }
    else if (type == 1)
    {
        // YES_OR_NO_EVENT
        std::cout << "A strange voice asks: 'Will you run now?' [Y/N]: ";
        char answer;
        std::cin >> answer;
        if (answer == 'y' || answer == 'Y')
        {
            if (rand() % 2 == 0)
            {
                std::cout << "You escape the encounter!\n";
				ClearCombat();
                Fighting = false;
				return;
            }
            else
            {
                std::cout << "It refuses to let you escape!\n";
            }
        }
        else
        {
            std::cout << "You stand your ground.\n";
        }
    }
    else if (type == 2)
    {
        // ITEMS_EVENT
        int food = rand() % 2;
        int water = rand() % 2;
        world->GetFood()->AddQuantity(food);
        world->GetWater()->AddQuantity(water);
        std::cout << "You found a hidden cache: +" << food << " food, +" << water << " water.\n";
    }
    else
    {
        // CHOOSE_SOMEONE_EVENT
        std::cout << "A hostile creature singles a party member out!\n";
        std::cout << "Who will you protect?\n";

        int livingParty[3];
        int livingCount = 0;

        for (int i = 0; i < ActivePartyCount; i++)
        {
            if (ActiveParty[i] != nullptr && ActiveParty[i]->IsAlive())
            {
                livingParty[livingCount++] = i;
                std::cout << "[" << livingCount << "] "
                          << ActiveParty[i]->GetName()
                          << " | HP: " << ActiveParty[i]->GetHealthPoints()
                          << " | ATK: " << GetCombatAttack(ActiveParty[i])
                          << "\n";
            }
        }

        if (livingCount == 0)
        {
            std::cout << "There are no living party members to protect.\n";
        }
        else
        {
            std::cout << "Choose a party member (1-" << livingCount << "): ";
            int choice;
            std::cin >> choice;

            if (choice >= 1 && choice <= livingCount)
            {
                int partyIndex = livingParty[choice - 1];
                Defending[partyIndex] = true;
                std::cout << ActiveParty[partyIndex]->GetName()
                          << " prepares to defend.\n";
            }
            else
            {
                std::cout << "Nobody was protected.\n";
            }
        }
    }

    std::cout << "----------------\n";
}

//junlong
void Game::RunCombat()
{
    Fighting = true;
    for (int i = 0; i < 3; i++) { Defending[i] = false; EnemyDefending[i] = false; }

    int round = 1;
    while (EnemyCount > 0 && isRunning && player->IsAlive())
    {
        bool anyEnemyAlive = false;
        for (int i = 0; i < EnemyCount; i++)
        {
            if (Enemies[i] != nullptr && Enemies[i]->IsAlive()) { anyEnemyAlive = true; }
        }
        if (!anyEnemyAlive) { break; }

        bool anyPartyAlive = false;
        for (int i = 0; i < ActivePartyCount; i++)
        {
            if (ActiveParty[i] != nullptr && ActiveParty[i]->IsAlive()) { anyPartyAlive = true; }
        }
        if (!anyPartyAlive) { break; }

        std::cout << "\n\n========== ROUND " << round++ << " ==========\n";
        TriggerCombatScenario();

        for (int i = 1; i < SafePlayerCount; )
        {
            Entity* survivor = SafePlayers[i];
            if (survivor != nullptr && !survivor->IsAlive())
            {
                RemoveDeadSurvivor(survivor);
            }
            else
            {
                i++;
            }
        }

        if (!player->IsAlive())
        {
            CheckForPlayerDeath();
            break;
        }
        if (EnemyCount == 0) { break; }

        for (int i = 0; i < ActivePartyCount && player->IsAlive(); i++)
        {
            if (!ActiveParty[i]->IsAlive()) { continue; }
            PlayerCombatTurn(i);
            bool remaining = false;
            for (int j = 0; j < EnemyCount; j++)
            {
                if (Enemies[j] != nullptr && Enemies[j]->IsAlive()) { remaining = true; }
            }
            if (!remaining) { break; }
        }

        for (int i = 0; i < EnemyCount && player->IsAlive(); i++)
        {
            if (Enemies[i] != nullptr && Enemies[i]->IsAlive())
            {
                EnemyCombatTurn(i);
            }
        }

        if (!player->IsAlive())
        {
            CheckForPlayerDeath();
            break;
        }
    }

    if (player->IsAlive() && EnemyCount > 0)
    {
        bool anyEnemyAlive = false;
        for (int i = 0; i < EnemyCount; i++)
        {
            if (Enemies[i] != nullptr && Enemies[i]->IsAlive()) { anyEnemyAlive = true; }
        }
        if (!anyEnemyAlive) { std::cout << "\nYou won the battle!\n"; }
    }

    ClearCombat();
    Fighting = false;
}

// Remove a dead recruited survivor from every active collection that references them.
void Game::RemoveDeadSurvivor(Entity* survivor)
{
    if (survivor == nullptr || survivor == player || survivor->IsAlive())
    {
        return;
    }

    for (int i = 0; i < ActivePartyCount; i++)
    {
        if (ActiveParty[i] == survivor)
        {
            for (int j = i; j < ActivePartyCount - 1; j++)
            {
                ActiveParty[j] = ActiveParty[j + 1];
            }
            ActiveParty[ActivePartyCount - 1] = nullptr;
            ActivePartyCount--;
            break;
        }
    }

    int safePlayerIndex = -1;
    for (int i = 1; i < SafePlayerCount; i++)
    {
        if (SafePlayers[i] == survivor)
        {
            safePlayerIndex = i;
            break;
        }
    }

    if (safePlayerIndex == -1)
    {
        return;
    }

    std::string deadName = survivor->GetName();

    for (int i = 0; i < 10; i++)
    {
        if (SafePlayerNames[i] == deadName)
        {
            UsedNames[i] = false;
            break;
        }
    }

    for (int i = safePlayerIndex; i < SafePlayerCount - 1; i++)
    {
        SafePlayers[i] = SafePlayers[i + 1];
    }

    SafePlayers[SafePlayerCount - 1] = nullptr;
    SafePlayerCount--;

    delete survivor;
}

//junlong
void Game::CheckForPlayerDeath()
{
    if (player == nullptr || player->IsAlive() || deathEndingTriggered)
    {
        return;
    }

    deathEndingTriggered = true;

    int survivorsAlive = 0;
    for (int i = 1; i < SafePlayerCount; i++)
    {
        if (SafePlayers[i] != nullptr && SafePlayers[i]->IsAlive())
        {
            survivorsAlive++;
        }
    }

    int daysSurvived = 0; 
    if (world != nullptr) 
    { 
        daysSurvived = world->getDays(); 
    }
    else 
    { 
        daysSurvived = 0; 
    }
    Endings.DeathEnding(
        daysSurvived,
        survivorsAlive
    );

    isRunning = false;
    Fighting = false;
}

//junlong
void Game::ClearCombat()
{
    for (int i = 0; i < maxEnemies; i++)
    {
        delete Enemies[i];
        Enemies[i] = nullptr;
    }
    EnemyCount = 0;
    for (int i = 0; i < 3; i++) { 
        Defending[i] = false; 
        EnemyDefending[i] = false; 
    }
}

//junlong
void Game::StartRandomEncounter()
{
    if (!isOutsideHouse || Fighting || !player->IsAlive())
    {
        return;
    }

    // 20% encounter chance per successful step.
    if (rand() % 100 >= 1)
    {
        return;
    }

    ClearCombat();
    EnemyCount = 1 + rand() % 2;

    for (int i = 0; i < EnemyCount; i++)
    {
        int hp = 45 + rand() % 36;
        int atk = 6 + rand() % 5;
        Enemies[i] = new Entity("Skinwalker " + std::to_string(i + 1), hp, atk, true, 'X');
    }

    std::cout << "\n";
    ConsoleColor::Print("!!! AN ENEMY APPEARED !!!\n", ConsoleColor::BRIGHT_RED);
    std::cout << "Your party enters combat!\n";

    // Skinwalkers have a chance to trigger a text-based jumpscare
    // immediately before combat begins.
    if (rand() % 100 < 100)
    {
        skinwalkerjumpscare::ShowSkinwalkerJumpscare();
    }

    RunCombat();
}

void Game::DisplayEquipmentFor(Entity* entity)
{
    if (entity == nullptr)
    {
        return;
    }
    Equipment* gear = GetCombatEquipment(entity);
    std::cout << entity->GetName() << " equipped: "
              << (gear ? gear->GetName() : "NONE") << "\n";
}

void Game::EquipStoredItemToSafePlayer()
{
    Inventory& inventory = player->GetInventory();
    if (inventory.GetItemCount() == 0)
    {
        std::cout << "There are no stored items.\n";
        return;
    }

    std::cout << "\nChoose stored equipment:\n";
    for (int i = 0; i < inventory.GetItemCount(); i++)
    {
        Object* item = inventory.GetItem(i);
        Equipment* equipment = dynamic_cast<Equipment*>(item);
        if (equipment != nullptr)
        {
            std::cout << "[" << i + 1 << "] " << equipment->GetName() << "\n";
        }
    }

    int itemChoice;
    std::cout << "Item: ";
    std::cin >> itemChoice;
    itemChoice--;

    Object* item = inventory.GetItem(itemChoice);
    Equipment* equipment = dynamic_cast<Equipment*>(item);
    if (equipment == nullptr)
    {
        std::cout << "That item is not equipment.\n";
        return;
    }

    std::cout << "\nWho should equip it?\n";
    for (int i = 0; i < SafePlayerCount; i++)
    {
        if (SafePlayers[i] != nullptr && SafePlayers[i]->IsAlive())
        {
            std::cout << "[" << i + 1 << "] " << SafePlayers[i]->GetName() << "\n";
        }
    }

    int targetChoice;
    std::cout << "Person: ";
    std::cin >> targetChoice;
    targetChoice--;

    if (targetChoice < 0 || targetChoice >= SafePlayerCount || SafePlayers[targetChoice] == nullptr)
    {
        std::cout << "Invalid person.\n";
        return;
    }

    Entity* target = SafePlayers[targetChoice];

    if (target == player)
    {
        if (player->GetInventory().GetEquippedGear() != nullptr)
        {
            std::cout << "The player already has equipment equipped. Store it first.\n";
            return;
        }
        player->GetInventory().EquipItem(itemChoice);
        return;
    }

    if (target->GetEquippedGear() != nullptr)
    {
        std::cout << target->GetName() << " already has equipment equipped.\n";
        return;
    }

    Object* taken = inventory.TakeItem(itemChoice);
    Equipment* takenEquipment = dynamic_cast<Equipment*>(taken);
    if (takenEquipment != nullptr && target->EquipGear(takenEquipment))
    {
        std::cout << target->GetName() << " equipped " << takenEquipment->GetName() << ".\n";
    }
    else
    {
        // This should only occur if the item/target became invalid.
        if (taken != nullptr)
        {
            inventory.AddItem(taken);
        }
        std::cout << "Could not equip the item.\n";
    }
}

Game::~Game()
{
    ClearCombat();

    // Player and House are owned by Game, not by the map chunks. Remove
    // every map reference before World/Chunks are destroyed.
    if (world != nullptr)
    {
        for (int i = 0; i < 5; i++)
        {
            world->GetChunks(i).RemoveObject(player);
            world->GetChunks(i).RemoveObject(house);
        }
    }

    delete world;
    world = nullptr;

    for (int i = 1; i < SafePlayerCount; i++)
    {
        delete SafePlayers[i];
        SafePlayers[i] = nullptr;
    }
    SafePlayerCount = 1;

    delete player;
    player = nullptr;

    delete house;
    house = nullptr;
}
