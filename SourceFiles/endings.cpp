#include "endings.h"
#include <iostream>

void endings::DeathEnding()
{
	std::cout << " The skinwalkers got to you... You died." << std::endl;

}

void endings::MilitaryEnding()
{
	std::cout << "The Military have come to rescue you. Congradulations, you win!" << std::endl;
}

void endings::helicopterEnding()
{
	std::cout << "You escape safely on a helicopter. Congradulations, you win!" << std::endl;
}
