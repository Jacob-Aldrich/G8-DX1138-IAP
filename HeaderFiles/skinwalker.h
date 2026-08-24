#pragma once
#include <string>
#include "Entity.h"

class skinwalker : public Entity
{
private:
	int SWHealthPoints;
	int SWAttackPoints;
	int imagechoice;

public:
	skinwalker();

	void dialogue();
	void setDialogue(int randomiser);

	/*int GetSWHealthPoints(int SWHealthPoints);
	int GetSWAttackPoints(int SWAttackPoints);*/

	//skinwalker image();

	//bool IsLetIn();

	void choiceDialogue();
	void battle() const;
	void wildbattle() const;
	void displayImage() const;
};
