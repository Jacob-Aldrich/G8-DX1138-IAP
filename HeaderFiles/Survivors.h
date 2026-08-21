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

public:
	Survivors();
	int GetNoOfSurvivors() const;

	void dialogue();
	void setDialogue(int randomiser);
	void scavenging();

	//int GetSHealthPoints(int SHealthPoints);
	//int GetSAttackPoints(int SAttackPoints);


	//Survivors image();

	//bool IsLetIn();

	void choiceDialogue();
	//void battle() const;
	void displayImage() const;

};




