#include "Game.h"
#include "World.h"
#include "Object.h"
#include "Entity.h"
#include "Equipment.h"

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
        displayStatus();
        std::cout << "\n> What will you do?\n\n";
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
                world->SearchForSupplies();
            else
                LookForSurvivors();
        }
    }

    isRunning = true;
}

void Game::Run()
{
    Turns = 5;

    while (isRunning)
    {
        if (!player->IsAlive())
        {
            Endings.DeathEnding();
            isRunning = false;
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
                        player->GetInventory().EquipItem(itemChoice);
                    else
                        std::cout << "This object cannot be equipped.\n";
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
                std::cout << "[EMPTY]\n";
            else
            {
                for (int i = 0; i < inventory.GetItemCount(); i++)
                {
                    Object* object = inventory.GetItem(i);
                    if (object != nullptr)
                        std::cout << "[" << i + 1 << "] " << object->GetName() << " x1\n";
                }
            }

            std::cout << "\nStorage " << inventory.GetItemCount()
                      << "/" << inventory.GetMaximumItems() << "\n";
            DisplayEquipmentFor(player);
            for (int i = 1; i < SafePlayerCount; i++)
                DisplayEquipmentFor(SafePlayers[i]);

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
            displayStatus();
            displayLegend();
            std::cout << "\nMove with W/A/S/D\nInteract with objects with E\n";
            std::cout << "Open/Close Inventory with B\n\n";
            world->GetChunks(world->getCurrentChunk()).PrintChunk(world->getCurrentChunk());
            world->displayInteractionOptions(player);

            int keypress = _getch();
            world->HandleKeypress(keypress, player);

            if (keypress == 'b' || keypress == 'B')
                insideInventoryMenu = true;
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
        std::cout << "[4] Go out of the house -- THIS WILL SKIP ALL TURNS\n";
        std::cin >> choice;

        if (choice == '1')
            EatFood();
        else if (choice == '2')
            DrinkWater();
        else if (choice == '3')
            insideHouseInventoryMenu = true;
        else if (choice == '4')
        {
            goOutsideHouse();
            Turns = 1;
            useTurn();
        }
        else
            std::cout << "Invalid choice. Please choose again.\n";
    }
}

int Game::getTurns() { return Turns; }

void Game::useTurn()
{
    Turns--;
    if (Turns <= 0)
    {
        Turns = maxTurns;
        world->addDays(1);
        DecreaseSafePlayerNeeds();
    }
}

void Game::LookForSurvivors()
{
    if (SafePlayerCount < 4)
    {
        int RandomHP = rand() % 41 + 80;
        int RandomATK = rand() % 4 + 2;
        int RandomName = rand() % 10;
        while (UsedNames[RandomName])
            RandomName = rand() % 10;

        UsedNames[RandomName] = true;
        SafePlayers[SafePlayerCount] = new Entity(
            SafePlayerNames[RandomName], RandomHP, RandomATK, false, 'A');

        std::cout << "You found " << SafePlayers[SafePlayerCount]->GetName() << "!\n";
        std::cout << "Attack: " << SafePlayers[SafePlayerCount]->GetBaseAttackPoints() << "\n";
        std::cout << "HP: " << SafePlayers[SafePlayerCount]->GetHealthPoints() << "\n";
        SafePlayerCount++;
    }
    else
        std::cout << "You cannot recruit any more survivors!\n";
}

void Game::clearConsole() { std::cout << "\033[H\033[2J"; }

void Game::displayInventory()
{
    std::cout << "Food: " << world->GetFood()->GetQuantity() << "/" << world->GetFood()->GetMaximumQuantity() << "\n";
    std::cout << "Water: " << world->GetWater()->GetQuantity() << "/" << world->GetWater()->GetMaximumQuantity() << "\n";
}

void Game::displaySurvivors()
{
    for (int i = 0; i < SafePlayerCount; i++)
    {
        if (SafePlayers[i] == nullptr) continue;
        std::cout << "Safe Player " << i + 1 << ": " << SafePlayers[i]->GetName()
                  << " | HP: " << SafePlayers[i]->GetHealthPoints()
                  << " | Hunger: " << SafePlayers[i]->GetHunger()
                  << " | Thirst: " << SafePlayers[i]->GetThirst() << "\n";
    }
}

void Game::displaySafePlayerNeeds()
{
    std::cout << "\nSafe Player Needs:\n";
    for (int i = 0; i < SafePlayerCount; i++)
    {
        if (SafePlayers[i] == nullptr || !SafePlayers[i]->IsAlive()) continue;
        std::cout << "[" << i + 1 << "] " << SafePlayers[i]->GetName()
                  << " | Hunger: " << SafePlayers[i]->GetHunger() << "/100"
                  << " | Thirst: " << SafePlayers[i]->GetThirst() << "/100\n";
    }
}

void Game::displayHouseWarnings()
{
    for (int i = 0; i < SafePlayerCount; i++)
    {
        if (SafePlayers[i] == nullptr || !SafePlayers[i]->IsAlive()) continue;
        if (SafePlayers[i]->GetHunger() < 100)
            std::cout << SafePlayers[i]->GetName() << " is hungry.\n";
        if (SafePlayers[i]->GetThirst() < 100)
            std::cout << SafePlayers[i]->GetName() << " is thirsty.\n";
    }
}

void Game::DecreaseSafePlayerNeeds()
{
    for (int i = 0; i < SafePlayerCount; i++)
    {
        if (SafePlayers[i] == nullptr || !SafePlayers[i]->IsAlive()) continue;
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
    bool fed[10] = { false };
    bool fedAnyone = false;

    while (!world->GetFood()->IsEmpty())
    {
        std::cout << "\nWho do you want to feed? (0 = done)\n";
        int choice;
        std::cin >> choice;
        if (choice == 0) break;
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

    if (fedAnyone) useTurn();
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
        if (choice == 0) break;
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

    if (drankAnyone) useTurn();
}

void Game::displayStatus()
{
    displayInventory();
    displaySurvivors();
    std::cout << "Player HP: " << player->GetHealthPoints() << "/100\n";
    std::cout << "Player Hunger: " << player->GetHunger() << "/100\n";
    std::cout << "Player Thirst: " << player->GetThirst() << "/100\n";
}

void Game::displayLegend()
{
    std::cout << "Legend:\nP: Player | F: Food | W: Water | S: Sword | G: Gun | H: House\n";
}

void Game::displayCurrentChunk()
{
    std::cout << "You are at Chunk: " << world->getCurrentChunk() << "\n";
}

House* Game::getHouse() { return house; }

void Game::ChooseOutsideParty()
{
    ActiveParty[0] = player;
    ActivePartyCount = 1;

    if (SafePlayerCount <= 1)
    {
        player->GetInventory().SetCapacityBonus(0);
        return;
    }

    std::cout << "\nChoose who to bring outside. Player is always included.\n";
    std::cout << "You can bring up to TWO companions.\n\n";
    displaySurvivors();

    bool chosen[10] = { false };
    int selected = 0;
    while (selected < 2)
    {
        std::cout << "Choose a survivor (0 = done): ";
        int choice;
        std::cin >> choice;
        if (choice == 0) break;
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

void Game::goOutsideHouse()
{
    ChooseOutsideParty();
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
    Fighting = false;

    player->GetInventory().TransferSupplies(world->GetFood(), world->GetWater());
    player->GetInventory().SetCapacityBonus(0);

    world->GetChunks(world->getCurrentChunk()).RemoveObject(player);
    world->GetChunks(world->getCurrentChunk()).RemoveObject(house);
    world->DeleteAllObjects();

    for (int i = 0; i < 3; i++) ActiveParty[i] = nullptr;
    ActivePartyCount = 0;
}

void Game::SetFighting(bool isFighting) { Fighting = isFighting; }
void Game::SetInsideInventoryMenu(bool value) { insideInventoryMenu = value; }
void Game::SetInsideHouseInventoryMenu(bool value) { insideHouseInventoryMenu = value; }

bool Game::IsInActiveParty(Entity* entity)
{
    for (int i = 0; i < ActivePartyCount; i++)
        if (ActiveParty[i] == entity) return true;
    return false;
}

Equipment* Game::GetCombatEquipment(Entity* entity)
{
    if (entity == player)
        return player->GetInventory().GetEquippedGear();
    return entity->GetEquippedGear();
}

int Game::GetCombatAttack(Entity* entity)
{
    Equipment* gear = GetCombatEquipment(entity);
    int base = entity->GetBaseAttackPoints();
    if (gear == nullptr) return base;

    if (gear->DoesSetAttackExactly())
        return gear->GetAttackValue();

    if (gear->IsInstantDefeatGear())
        return base;

    return base + gear->GetAttackValue();
}

int Game::CalculateCombatDamage(Entity* attacker, Entity* defender, bool& veryEffective, bool& notEffective)
{
    veryEffective = false;
    notEffective = false;

    Equipment* gear = GetCombatEquipment(attacker);
    double multiplier = 1.0;

    if (gear != nullptr)
    {
        if (gear->GetType() == ItemType::GUN && defender->GetIsSkinWalker())
            multiplier = 1.5;
        else if (gear->GetType() == ItemType::SWORD && defender->GetIsSkinWalker())
            multiplier = 0.75;
    }

    // Small random damage variation keeps combat from being identical.
    double randomMultiplier = (rand() % 21 + 90) / 100.0;
    int damage = static_cast<int>(GetCombatAttack(attacker) * multiplier * randomMultiplier);
    if (damage < 1) damage = 1;

    if (multiplier >= 1.4)
        veryEffective = true;
    if (multiplier <= 0.75)
        notEffective = true;

    return damage;
}

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
        if (gear) std::cout << " [" << gear->GetName() << "]";
        std::cout << "\n";
    }

    std::cout << "\nENEMIES\n";
    for (int i = 0; i < EnemyCount; i++)
    {
        if (Enemies[i] == nullptr) continue;
        std::cout << "[" << i + 1 << "] " << Enemies[i]->GetName()
                  << " HP " << Enemies[i]->GetHealthPoints()
                  << " ATK " << Enemies[i]->GetBaseAttackPoints() << "\n";
    }
    std::cout << "============================\n";
}

void Game::PlayerCombatTurn(int partyIndex)
{
    Entity* attacker = ActiveParty[partyIndex];
    if (!attacker->IsAlive()) return;

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
        if (veryEffective) std::cout << "VERY EFFICIENT!\n";
        else if (notEffective) std::cout << "NOT EFFICIENT\n";
        if (!Enemies[targetChoice]->IsAlive()) std::cout << Enemies[targetChoice]->GetName() << " was defeated!\n";
        return;
    }
}

void Game::SurvivorCombatTurn(int partyIndex)
{
    Entity* attacker = ActiveParty[partyIndex];
    if (!attacker->IsAlive()) return;

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
    if (target < 0) return;

    Equipment* gear = GetCombatEquipment(attacker);
    if (gear != nullptr && gear->IsInstantDefeatGear() && gear->HasUsesRemaining())
    {
        gear->UseOnce();
        Enemies[target]->TakeDamage(Enemies[target]->GetHealthPoints());
        std::cout << attacker->GetName() << " used " << gear->GetName() << " and instantly defeated " << Enemies[target]->GetName() << "!\n";
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
    if (veryEffective) std::cout << "VERY EFFICIENT!\n";
    else if (notEffective) std::cout << "NOT EFFICIENT\n";
}

void Game::EnemyCombatTurn(int enemyIndex)
{
    Entity* enemy = Enemies[enemyIndex];
    if (enemy == nullptr || !enemy->IsAlive()) return;

    int living[3];
    int count = 0;
    for (int i = 0; i < ActivePartyCount; i++)
        if (ActiveParty[i] != nullptr && ActiveParty[i]->IsAlive()) living[count++] = i;
    if (count == 0) return;

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
        std::cout << target->GetName() << " has fallen!\n";
        if (target == player)
        {
            Endings.DeathEnding();
            isRunning = false;
        }
    }
}

void Game::TriggerCombatScenario()
{
    // 75% chance each combat round.
    if (rand() % 100 >= 75) return;

    int type = rand() % 4;
    std::cout << "\n--- SCENARIO ---\n";

    if (type == 0)
    {
        // SEND_SOMEONE_EVENT: one living companion takes a hit to protect the group.
        int candidates[3], count = 0;
        for (int i = 1; i < ActivePartyCount; i++)
            if (ActiveParty[i]->IsAlive()) candidates[count++] = i;

        if (count > 0)
        {
            Entity* target = ActiveParty[candidates[rand() % count]];
            int damage = 5 + rand() % 8;
            target->TakeDamage(damage);
            std::cout << target->GetName() << " steps in front of an attack and takes " << damage << " damage!\n";
        }
        else
            std::cout << "You hear something moving in the darkness...\n";
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
                std::cout << "It refuses to let you escape!\n";
        }
        else
            std::cout << "You stand your ground.\n";
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
        std::cout << "A hostile creature singles someone out!\n";
        std::cout << "Choose a party member to protect: ";
        int choice;
        std::cin >> choice;
        choice--;
        if (choice >= 0 && choice < ActivePartyCount && ActiveParty[choice]->IsAlive())
        {
            Defending[choice] = true;
            std::cout << ActiveParty[choice]->GetName() << " prepares to defend.\n";
        }
        else
            std::cout << "Nobody was protected.\n";
    }

    std::cout << "----------------\n";
}

void Game::RunCombat()
{
    Fighting = true;
    for (int i = 0; i < 3; i++) { Defending[i] = false; EnemyDefending[i] = false; }

    int round = 1;
    while (EnemyCount > 0 && isRunning && player->IsAlive())
    {
        bool anyEnemyAlive = false;
        for (int i = 0; i < EnemyCount; i++)
            if (Enemies[i] != nullptr && Enemies[i]->IsAlive()) anyEnemyAlive = true;
        if (!anyEnemyAlive) break;

        bool anyPartyAlive = false;
        for (int i = 0; i < ActivePartyCount; i++)
            if (ActiveParty[i] != nullptr && ActiveParty[i]->IsAlive()) anyPartyAlive = true;
        if (!anyPartyAlive) break;

        std::cout << "\n\n========== ROUND " << round++ << " ==========\n";
        TriggerCombatScenario();
        if (EnemyCount == 0) break;

        for (int i = 0; i < ActivePartyCount && player->IsAlive(); i++)
        {
            if (!ActiveParty[i]->IsAlive()) continue;
            PlayerCombatTurn(i);
            bool remaining = false;
            for (int j = 0; j < EnemyCount; j++)
                if (Enemies[j] != nullptr && Enemies[j]->IsAlive()) remaining = true;
            if (!remaining) break;
        }

        for (int i = 0; i < EnemyCount && player->IsAlive(); i++)
        {
            if (Enemies[i] != nullptr && Enemies[i]->IsAlive())
                EnemyCombatTurn(i);
        }

        if (!player->IsAlive())
        {
            Endings.DeathEnding();
            isRunning = false;
            break;
        }
    }

    if (player->IsAlive() && EnemyCount > 0)
    {
        bool anyEnemyAlive = false;
        for (int i = 0; i < EnemyCount; i++)
            if (Enemies[i] != nullptr && Enemies[i]->IsAlive()) anyEnemyAlive = true;
        if (!anyEnemyAlive) std::cout << "\nYou won the battle!\n";
    }

    ClearCombat();
    Fighting = false;
}

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

void Game::StartRandomEncounter()
{
    if (!isOutsideHouse || Fighting || !player->IsAlive()) return;

    // 20% encounter chance per successful step.
    if (rand() % 100 >= 20) return;

    ClearCombat();
    EnemyCount = 1 + rand() % 2;

    for (int i = 0; i < EnemyCount; i++)
    {
        int hp = 45 + rand() % 36;
        int atk = 6 + rand() % 5;
        Enemies[i] = new Entity("Skinwalker " + std::to_string(i + 1), hp, atk, true, 'X');
    }

    std::cout << "\n!!! AN ENEMY APPEARED !!!\n";
    std::cout << "Your party enters combat!\n";
    RunCombat();
}

void Game::DisplayEquipmentFor(Entity* entity)
{
    if (entity == nullptr) return;
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
            std::cout << "[" << i + 1 << "] " << equipment->GetName() << "\n";
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
            std::cout << "[" << i + 1 << "] " << SafePlayers[i]->GetName() << "\n";
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
        if (taken != nullptr) inventory.AddItem(taken);
        std::cout << "Could not equip the item.\n";
    }
}

Game::~Game()
{
    if (isOutsideHouse)
    {
        world->GetChunks(world->getCurrentChunk()).RemoveObject(player);
        world->GetChunks(0).RemoveObject(house);
    }

    ClearCombat();
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
}
