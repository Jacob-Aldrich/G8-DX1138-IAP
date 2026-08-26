#pragma once
#include "Entity.h"
#include "Inventory.h"

//junlong
class Player : public Entity
{
private:
	Inventory inventory;

public:
	Player();
	~Player();

	Inventory& GetInventory();
};
