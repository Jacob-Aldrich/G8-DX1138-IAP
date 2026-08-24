#pragma once
#include "Entity.h"
class Survivors :
    public Entity
{
private:
    int SHealthPoints;
    int SAttackPoints;
    int imagechoice;
	int NoOfSurvivors;

	int Hunger;
	int Thirst;

	int breadCount;
	int waterCount;
	int medicalKitCount;

public:
	Survivors();
	int GetNoOfSurvivors() const;

	void dialogue();
	void setDialogue(int randomiser);
	void scavenging();

	void SetHunger(int value);
	void SetThirst(int value);
	int GetHunger() const;
	int GetThirst() const;

	void EndTurn();

	// Consumables
	void ConsumeBread();
	void ConsumeWater();
	void ConsumeMedicalKit();

	// Decrease hunger/thirst
	void ReduceHunger(int amount);
	void ReduceThirst(int amount);

	// Display status
	void DisplayStatus() const;

	void displayImage() const;

	//int GetSHealthPoints(int SHealthPoints);
	//int GetSAttackPoints(int SAttackPoints);


	//Survivors image();

	//bool IsLetIn();

	void choiceDialogue();
	//void battle() const;


};

