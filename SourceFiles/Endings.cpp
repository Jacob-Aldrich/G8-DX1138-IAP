#include "endings.h"
#include <iostream>

void endings::DeathEnding()
{
	std::cout << " You couldn't tough it out... You died." << std::endl;
	return;
}

void endings::MilitaryEnding()
{
	std::cout << "The Military have come to rescue you. Congradulations, you win!" << std::endl;
	//as of now cannot get this ending yet 
}

void endings::HelicopterEnding()
{
	std::cout << "You escape safely on a helicopter. Congratulations, you win!" << std::endl;
	// this one also cannot yet lol
}
