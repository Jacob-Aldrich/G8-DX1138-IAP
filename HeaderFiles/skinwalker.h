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

	virtual void dialogue();
	void setDialogue(int randomiser);

	int GetSWHealthPoints();
	int GetSWAttackPoints();

	skinwalker image();

	bool IsLetIn();

	void choiceDialogue();
	void battle();
	void wildbattle();
	void displayImage();
};
