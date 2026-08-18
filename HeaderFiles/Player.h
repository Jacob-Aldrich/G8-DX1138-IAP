#pragma once
#include"Entity.h"
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

public:
	Player();

	void Speak(int choice);

	std::string GetLook0();
	std::string GetLook1();
	std::string GetLook2();
	std::string GetLook3();
	std::string GetLook4();

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

