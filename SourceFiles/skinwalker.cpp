#include "skinwalker.h"
#include <iostream>
void skinwalker::dialogue()
{
	int randomiser = rand() % 3;
	//setDialogue(randomiser);

	if (randomiser == 0)
	{
		std::cout << "PleAse hElp mE, I neeD sheltEr." << std::endl;
	}
	else if (randomiser == 1)
	{
		std::cout << "Hey, could you let me in? I've got some suplies to share." << std::endl;
	}
	else
	{
		std::cout << "...Young one... Let me in." << std::endl;
	}
}

