#pragma once
#include"Entity.h"
#include <string>

class Player : public Entity
{
private:
	std::string Look0, Look1, Look2, Look3, Look4;

	std::string Dialogue1, Dialogue2, Dialogue3;

	//Player's states
	int hunger;
	int thirst;

	//Encounter flags
	bool skinwalkerEncounter;
	bool survivorsEncounter;

	int breadCount;
	int waterCount;
	int medicalKitCount;

public:
	Player();

	void UpdateOverTime();
	bool IsDead();

	void Speak(int choice);

	std::string GetLook0(); //happy
	std::string GetLook1(); //angry
	std::string GetLook2(); //bored
	std::string GetLook3(); //shocked
	std::string GetLook4(); //dead

	//show in grid
	char GetGridSymbol();
	void DisplayStatus();

	//Item pickup
	void PickUpBread();
	void PickUpWater();
	void PickUpKnife();
	void PickUpMedicalKit();

	//bag actions
	void ShowBag();
	void ConsumeBread();
	void ConsumeWater();
	void ConsumeMedicalKit();
	void DropBread();
	void DropWater();
	void DropMedicalKit();

	//Encounters
	void EncounterSkinwalker();
	void EncounterSurvivors();

	//skinwalker
	bool SkinwalkerAtDoor();
	//bool EncounterSkinwalker();
	//actions
	void SkinWalkerAtDoor(int choice);
	void EncounterSkinwalker(int choice);

	//survivors
	bool SurvivorsAtDoor();
	//bool EncounterSurvivors();
	//actions
	void SurvivorsAtDoor(int choice);
	//void EncounterSurvivors(int choice);

	void BattleSkinwalker();

	void SetHunger(int value);
	void SetThirst(int value);
	int GetHunger() const;
	int GetThirst() const;

};
