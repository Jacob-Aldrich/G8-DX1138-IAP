#pragma once

#include "Object.h"

//brandon
class Equipment;
class Material;

class Inventory
{
private:
	static const int MaximumItems = 20;
	static const int BaseCapacity = 10;
	int CapacityBonus;

	Object* Items[MaximumItems];
	int ItemCount;

	Equipment* EquippedGear;

public:
	Inventory();
	~Inventory();

	// Normal inventory
	bool AddItem(Object* object);
	bool RemoveItem(int inventoryIndex);
	Object* TakeItem(int inventoryIndex);
	void SetCapacityBonus(int bonus);

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