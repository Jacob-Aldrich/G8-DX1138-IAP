#include "endings.h"
#include <iostream>
#include <conio.h>

void endings::DeathEnding()
{
	std::cout << "You died." << std::endl;
	std::cout << "PRESS ANY KEY TO CONTINUE..." << std::endl;
	char keypress = _getch();
}

void endings::MilitaryEnding()
{
	std::cout << "The Military have come to rescue you." << std::endl;
	std::cout << "PRESS ANY KEY TO CONTINUE..." << std::endl;
	char keypress = _getch();
	//as of now cannot get this ending yet
}

void endings::HelicopterEnding()
{
	std::cout << "You escape safely on a helicopter." << std::endl;
	std::cout << "PRESS ANY KEY TO CONTINUE..." << std::endl;
	char keypress = _getch();
}
