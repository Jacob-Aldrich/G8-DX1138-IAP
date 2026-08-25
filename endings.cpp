#include "endings.h"
#include <iostream>
#include <conio.h>

void endings::DeathEnding()
{
	std::cout << "The skinwalkers got to you... You died." << std::endl;
	std::cout << "PRESS ANY KEY TO CONTINUE..." << std::endl;
	char keypress = _getch();
}

void endings::MilitaryEnding()
{
	std::cout << "The Military have come to rescue you. Congradulations, you win!" << std::endl;
	//as of now cannot get this ending yet 
}

void endings::HelicopterEnding()
{
	std::cout << "You escape safely on a helicopter. Congradulations, you win!" << std::endl;
	// this one also cannot yet lol
}
