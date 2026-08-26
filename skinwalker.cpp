#include "skinwalker.h"
#include "ConsoleColors.h"
#include "Game.h"

#include <conio.h>
#include <cstdlib>
#include <iostream>

Skinwalker::Skinwalker(std::string name)
    : Entity(name, 65, 8, true, 'X')
{
}

void Skinwalker::dialogue()
{
    int randomiser = rand() % 3;

    ConsoleColor::Print("Stranger: ", ConsoleColor::BRIGHT_YELLOW);

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

namespace skinwalkerjumpscare
{
    void ShowSkinwalkerJumpscare()
    {
        // The jumpscare is intentionally text-only so it works in the console.
        const char* face1 = R"SKIN(
                    ..     .            ..
                ....--+-.........--.--+-...--
               ...-+...--+---+-++--++-..-+-..-.
              ...-.---+---+--+-+--+-..-----+---
              .-----+---+-         -+..-+---+--.
             .-----+---+.           .+-.-+--++--.
            ...-+-----+.              +..-+-++-+.
            .-.-+++---..-.          ...+.-+++-.--.
           ...--+++-+###+-.       .++###+--#+--.--
           ...--. --+ .+###-     .+-##- +--- .-.--
          .-.---. --+.  ..         ... .---. ------
          .----+--+-+.        .        .+-+--+-----.
          .+--++---+++-.              -+++-.-+-----.
          .+--+++--+++++---++-..++++.+++++--++---+-
          .-+++++++++++#- -+------+ .#++++++++---+-
            -+-+++++++#- ----------+ .++++++++--+-
              -++++++-+##+--.---..-+###-+++++--+.
               .+++++++-+-----+-....+--#++++++.
                  .+++.-++---+.-----++.++++-
                    .. +#####-  ######.  -
                        .-...    .--
)SKIN";

        const char* face2 = R"SKIN(
                           :.:.... -:::.
                    ..:..---::..::---::: :-:---
                   *-=-==%%#=+::==*%%++: :++###=
                   :  .. ::::.  .. :..:   :..::.:
               . - --.-:-==-:-::-::=--:- -:----:-...
                 %=#+:++*%@%++-=+=%%%#++ ++*%%%=+-.#.
              .  :.:. ...:::......::::.. ..::::... :..
                 :.--.-::==.--:-=:.=-:-- --::-..=::-:.
              :. @.%--+=+%%:=+:*#=+@#**# ##**#--#*:=+.
             ..: - #-:-=+-*=---:*--#+-== :+==#-:=::= +:
                   .    -    .:::. ::.:  - .    ::. :-:
               : :=   .      .  .=.#== .         =:%=:= 
              :- % := =  .   -.-.-% =: :   :. *  ..#*
               :   =-:-      ::- .+.. := ==::=   :.=.-
                 ...:.  .  . .  . ::.:...--:=:.. :.:.:
               --*=.  - +. .:-    . ++.-.=*-+#: .=:-.+
            . . -=:=:.. -=-. :       .-   -  -..:-.- -
                : .:  ...  .        ... ..:.:: ... ...
                : %**::- ## + :- -=+ -:=-.%*+###==-.%
                  --- .-:-      . .==-.:. :-:==: =:
                             ...:  :..:: ::     :.
                   .:.   ..  -:.+=#*+**+ +.   . #
                   .::  .  = =.:: +.---- -:: :..
                      :.        :     :..::  :..
                      := - --*- +.-:+:**.=#=**
                      :.+ .- #:.%:%#++*=.*%+#%
                      . =...: :-. -=::-.  -::- 
                      -    ..=:+=-.*=-+= -+.-
                        : #.+*-: +:%+=*- -#:
                        =. : : :+-.+=-=. -
)SKIN";

        Game::clearConsole();
        std::cout << "\n\n";
        std::cout << ConsoleColor::BRIGHT_RED << ConsoleColor::BOLD;
        std::cout << "              !!! SKINWALKER !!!\n\n";
        std::cout << ((rand() % 2 == 0) ? face1 : face2);
        std::cout << ConsoleColor::RESET;
        std::cout << "\n\n";
        std::cout << "Press any key to continue battle...";
        std::cout.flush();
        _getch();
        Game::clearConsole();
    }
}
