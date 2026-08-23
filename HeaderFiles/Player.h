#pragma once
#include "Entity.h"
#include "Inventory.h"

class Player : public Entity
{
private:
	Inventory inventory;

public:
	Player();
	~Player();
};
