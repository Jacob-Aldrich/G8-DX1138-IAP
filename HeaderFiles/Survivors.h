#pragma once
#include "Entity.h"
class Survivors :
    public Entity
{
private:
    int SHealthPoints;
    int SAttackPoints;
    int imagechoice;

public:
	Survivors();

	virtual void dialogue();
	void setDialogue(int randomiser);

	int GetSHealthPoints(int SHealthPoints);
	int GetSAttackPoints(int SAttackPoints);

	Survivors image();

	bool IsLetIn();

	void choiceDialogue() const;
	void battle() const;
	void displayImage() const;

};


