#pragma once

#include "Object.h"

class Equipment;
class Material;

class Inventory
{
private:
	static const int MaximumItems = 10;

	Object* Items[MaximumItems];
	int ItemCount;

	Equipment* EquippedGear;

public:
	Inventory();
	~Inventory();

	// Normal inventory
	bool AddItem(Object* object);
	bool RemoveItem(int inventoryIndex);

	// Equipment
	bool EquipItem(int inventoryIndex);
	bool EquipEquipment(Equipment* equipment);
	bool StoreEquippedItem();

	Equipment* GetEquippedGear();

	// Display
	void ShowInventory();
	void InventoryMenu();
	void HouseInventoryMenu();

	// Supplies
	void TransferSupplies(Material* foodSupply, Material* waterSupply);

	// Accessors
	int GetItemCount();
	int GetMaximumItems();
	Object* GetItem(int inventoryIndex);

	// Combat
	int GetAttackWithGear(int baseAttack);
};