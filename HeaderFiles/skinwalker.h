#pragma once
#include "Entity.h"

class skinwalker : public Entity
{
private:
	int SWHealthPoints;
	int SWAttackPoints;

public:
	virtual void dialogue();
	/*void setDialogue(int randomiser);
	skinwalker image();
	int GetSWHealthPoints();
	int GetSWAttackPoints();

	bool IsLetIn();*/
};
