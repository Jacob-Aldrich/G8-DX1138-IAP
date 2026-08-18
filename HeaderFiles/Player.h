#pragma once
#include"Entity.h"
#include <string>

class Player : public Entity
{
private:
    std::string Look;

    std::string Dialogue1;
    std::string Dialogue2;
	std::string Dialogue3;

public:
	Player();

	void Speak(int choice);

	void SetLook(const std::string& look);
	std::string GetLook();

	bool SkinwalkerAtDoor();
	bool EncounterSkinwalker();

	//actions
	void SkinWalkerAtDoor(int choice);
	void EncounterSkinwalker(int choice);




};


