#include "Player.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    // Create a Player object
    Player player;

    player.SetHunger(100);
    player.SetThirst(100);

    

    // Show starting stats from Entity
    std::cout << "Player HP: " << player.GetHealthPoints() << std::endl;
    std::cout << "Player Attack: " << player.GetBaseAttackPoints() << std::endl;
    std::cout << "Energy Bar: " << player.GetHunger() << std::endl;
    std::cout << "Hydration Bar: " << player.GetThirst() << std::endl;


    // Demonstrate dialogue
    std::cout << "\n--- Dialogue Demo ---" << std::endl;
    player.Speak(1);
    player.Speak(2);
    player.Speak(3);
    player.Speak(99); // default case

    // Demonstrate looks
    std::cout << "\n--- Player Looks ---" << std::endl;
    std::cout << player.GetLook0() << std::endl;
    std::cout << player.GetLook1() << std::endl;
    std::cout << player.GetLook2() << std::endl;
    std::cout << player.GetLook3() << std::endl;
    std::cout << player.GetLook4() << std::endl;

    // Demonstrate encounters (currently always false)
    std::cout << "\n--- Encounters ---" << std::endl;
    if (player.SkinwalkerAtDoor()) {
        player.SkinWalkerAtDoor(1);
    }
    else {
        std::cout << "No skinwalker at the door." << std::endl;
    }

    /*if (player.EncounterSkinwalker()) {
        player.EncounterSkinwalker(1);
    }
    else {
        std::cout << "No skinwalker encountered." << std::endl;
    }*/

    if (player.SurvivorsAtDoor()) {
        player.SurvivorsAtDoor(3);
    }
    else {
        std::cout << "No survivors at the door." << std::endl;
    }

    // Demonstrate combat
    std::cout << "\n--- Combat Demo ---" << std::endl;
    std::cout << "Player attacks for " << player.Attack() << " damage!" << std::endl;
    player.TakeDamage(30);
    std::cout << "Player HP after taking damage: " << player.GetHealthPoints() << std::endl;
    std::cout << "Is player alive? " << (player.IsAlive() ? "Yes" : "No") << std::endl;

	std::cout << "Player appears as: " << player.GetGridSymbol() << " on the grid." << std::endl;

	player.DisplayStatus();

    const int gridSize = 5;
    for (int y = 0; y < gridSize; y++) {
        for (int x = 0; x < gridSize; x++) {
            if (x == 2 && y == 2) { // player at center
                std::cout << player.GetGridSymbol() << " ";
            }
            else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }

    // Pick up items
    for (int i = 0; i < 12; i++) {
        player.PickUpBread();
        player.PickUpWater();
        player.PickUpMedicalKit();
    }
    player.PickUpKnife();

    player.ConsumeBread();
    player.ConsumeWater();
    player.ConsumeMedicalKit();
    player.ShowBag();

    player.DropBread();
    player.DropWater();
    player.DropMedicalKit();
    player.ShowBag();

    // Encounter events
    player.EncounterSkinwalker();
    player.GetGridSymbol(); // will show ASCII art
    player.EncounterSurvivors();
    player.GetGridSymbol(); // will show ASCII art

    //stimulate game time passing
    for (int i = 0; i < 150; i++) {
        player.UpdateOverTime();
        player.DisplayStatus();

        if (player.IsDead()) {
            std::cout << "Game Over: You have died." << std::endl;
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
