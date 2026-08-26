#pragma once
#include "World.h"
#include "Entity.h"
#include "endings.h"
#include "Scenarios.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <conio.h>

class Equipment;

class Game
{
    friend class Scenarios;
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
        "James", "Ethan", "Marcus", "Daniel", "Ryan",
        "Lucas", "Adrian", "Noah", "Jason", "Kevin"
    };

    Entity* SafePlayers[10] = { nullptr };
    int SafePlayerCount = 0;

    // The player is always in the party. Up to TWO recruited survivors
    // can be selected to accompany the player outside.
    Entity* ActiveParty[3] = { nullptr, nullptr, nullptr };
    int ActivePartyCount = 0;

    static int const maxEnemies = 3;
    Entity* Enemies[maxEnemies] = { nullptr };
    int EnemyCount = 0;
    bool Defending[3] = { false, false, false };
    bool EnemyDefending[3] = { false, false, false };

    static int const DailyHungerLoss = 33;
    static int const DailyThirstLoss = 33;
    static int const FoodRestoreAmount = 25;
    static int const WaterRestoreAmount = 25;
    static int const OutsideStoragePerCompanion = 5;

    bool UsedNames[10] = { false };
    endings Endings;
    Scenarios scenarios;

    Player* player = new Player();
    House* house = new House('H', 5, 5, "House", this);

    void ChooseOutsideParty();
    void ClearCombat();
    void RunCombat();
    void DisplayCombatStatus();
    void PlayerCombatTurn(int partyIndex);
    void SurvivorCombatTurn(int partyIndex);
    void EnemyCombatTurn(int enemyIndex);
    void TriggerCombatScenario();
    int CalculateCombatDamage(Entity* attacker, Entity* defender, bool& veryEffective, bool& notEffective);
    Equipment* GetCombatEquipment(Entity* entity);
    int GetCombatAttack(Entity* entity);
    void EquipStoredItemToSafePlayer();
    bool IsInActiveParty(Entity* entity);
    void DisplayEquipmentFor(Entity* entity);

public:
    Game();
    void Run();

    int getTurns();
    void useTurn();
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

    // Called by World after a successful outdoor step.
    void StartRandomEncounter();

    House* getHouse();
    void goOutsideHouse();
    void goInsideHouse();

    void SetFighting(bool isFighting);
    void SetInsideInventoryMenu(bool isInsideInventoryMenu);
    void SetInsideHouseInventoryMenu(bool value);

    ~Game();
};
