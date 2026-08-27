#include "endings.h"
#include <iostream>
#include <conio.h>
//wenya and shanelle

void endings::DeathEnding(int daysSurvived, int survivorsAlive)
{
    std::cout << "\n========================================\n";
    std::cout << "              DEATH ENDING\n";
    std::cout << "========================================\n";
    std::cout << "You died.\n\n";
    std::cout << "The Skinwalkers have consumed your flesh-\n"; 
    std::cout << "and body, and you eventually succumbed to-\nthe pain.\n\n";
    if (survivorsAlive > 0) {
		std::cout << "The Skinwalkers broke into your house and\nate every remaining survivor, leaving nothing behind.\n\n";
    }
    std::cout << "Your town is now a wasteland.\n\n";
    std::cout << "Days survived    : " << daysSurvived << "\n";
    std::cout << "\n----------------------------------------\n";
    std::cout << "                 THE END\n";
    std::cout << "----------------------------------------\n";
    std::cout << "PRESS ANY KEY TO CONTINUE..." << std::endl;
    char keypress = _getch();

    ShowCredits();
}
void endings::MilitaryEnding(int daysSurvived, int survivorsAlive)
{
    std::cout << "\n========================================\n";
    std::cout << "            MILITARY ENDING\n";
    std::cout << "========================================\n";
    std::cout << "The Military have come to rescue you.\n\n";
    std::cout << "After days of fighting to survive, you\n";
    std::cout << "finally see a chance to escape the town.\n\n";

    if (survivorsAlive > 0) {
        std::cout << "The remaining survivors have been rescued\n";
        std::cout << "alongside you.\n\n";
    }

    std::cout << "You leave the wasteland behind,\n";
    std::cout << "hoping to find safety elsewhere.\n\n";

    std::cout << "Days survived    : " << daysSurvived << "\n";
    std::cout << "\n----------------------------------------\n";
    std::cout << "                 THE END\n";
    std::cout << "----------------------------------------\n";
    std::cout << "PRESS ANY KEY TO CONTINUE..." << std::endl;

    char keypress = _getch();

    ShowCredits();
}

void endings::HelicopterEnding(int daysSurvived, int survivorsAlive)
{
    std::cout << "\n========================================\n";
    std::cout << "          HELICOPTER ENDING\n";
    std::cout << "========================================\n";
    std::cout << "You escape safely on a helicopter.\n\n";
    std::cout << "After everything you have endured, you\n";
    std::cout << "finally manage to escape the wasteland.\n\n";

    if (survivorsAlive > 0) {
        std::cout << "The remaining survivors escape with you,\n";
        std::cout << "finally reaching safety.\n\n";
    }

    std::cout << "The town disappears beneath you as the\n";
    std::cout << "helicopter carries you to safety.\n\n";

    std::cout << "Days survived    : " << daysSurvived << "\n";
    std::cout << "\n----------------------------------------\n";
    std::cout << "                 THE END\n";
    std::cout << "----------------------------------------\n";
    std::cout << "PRESS ANY KEY TO CONTINUE..." << std::endl;

    char keypress = _getch();

    ShowCredits();
}

//junlong
void endings::ShowCredits()
{
    std::cout << "\n========================================\n";
    std::cout << "              CREDITS\n";
    std::cout << "========================================\n";
    std::cout << "This game is brought to you by:\n\n";
    std::cout << "Gao Wenya (262745Y)\n";
    std::cout << "Lian Yi Xuan Shanelle(260627K)\n";
    std::cout << "Viloria Jacob Aldrich Pantig(264422K)\n";
    std::cout << "Kuan JunLong(251061F)\n";
    std::cout << "Chai Ji Xu Brandon(262090Z)\n\n";
    std::cout << "PRESS ANY KEY TO CONTINUE..." << std::endl;

    char keypress = _getch();
}
