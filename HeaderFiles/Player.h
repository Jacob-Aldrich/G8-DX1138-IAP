#pragma once
#include "Entity.h"
#include "Inventory.h"
#include <string>

class Player : public Entity
{
private:
    std::string Look0;
    std::string Look1;
    std::string Look2;
    std::string Look3;
    std::string Look4;

    std::string Dialogue1;
	std::string Dialogue2;
	std::string Dialogue3;

	Inventory GearInventory;

public:
	Player();
	~Player() override;

	bool AddEquipment(Equipment* equipment);
	bool EquipItem(int inventoryIndex);
	void ShowEquipment();
	void EquipmentMenu();

	int GetEquipmentCount();
	Equipment* GetEquipment(int inventoryIndex);
	Equipment* GetEquippedGear();
	int GetTotalAttackPoints();

	void Speak(int choice);

	std::string GetLook0(); // happy
	std::string GetLook1(); // angry
	std::string GetLook2(); // crying
	std::string GetLook3(); // shocked
	std::string GetLook4(); // bored

	bool SkinwalkerAtDoor();
	bool EncounterSkinwalker();

	//actions
	void SkinWalkerAtDoor(int choice);
	void EncounterSkinwalker(int choice);
	
	//survivors
	bool SurvivorsAtDoor();
	//bool EncounterSurvivors();

	//actions
	void SurvivorsAtDoor(int choice);
	//void EncounterSurvivors(int choice);


};
