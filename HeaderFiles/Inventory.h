#pragma once

#include "Equipment.h"

// Inventory owns the Gear collected by the Player.
class Inventory
{
private:
	static const int MaximumItems = 8;
	Equipment* Items[MaximumItems];
	int ItemCount;
	Equipment* EquippedGear;

public:
	Inventory();
	~Inventory();

	bool AddItem(Equipment* equipment);
	bool EquipItem(int inventoryIndex);
	void ShowInventory(int baseAttack);
	void InventoryMenu(int baseAttack);

	int GetItemCount();
	Equipment* GetItem(int inventoryIndex);
	Equipment* GetEquippedGear();
	int GetAttackWithGear(int baseAttack);
};
