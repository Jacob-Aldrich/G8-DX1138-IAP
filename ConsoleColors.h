#pragma once

#include <iostream>
#include <string>

// ANSI / ASCII escape colour codes for console output.
// The project already uses ANSI escape codes to clear the console, so these
// use the same system for coloured text.
namespace ConsoleColor
{
    constexpr const char* RESET = "\033[0m";
    constexpr const char* BOLD = "\033[1m";

    constexpr const char* BLACK = "\033[30m";
    constexpr const char* RED = "\033[31m";
    constexpr const char* GREEN = "\033[32m";
    constexpr const char* YELLOW = "\033[33m";
    constexpr const char* BLUE = "\033[34m";
    constexpr const char* MAGENTA = "\033[35m";
    constexpr const char* CYAN = "\033[36m";
    constexpr const char* WHITE = "\033[37m";

    constexpr const char* BRIGHT_BLACK = "\033[90m";
    constexpr const char* BRIGHT_RED = "\033[91m";
    constexpr const char* BRIGHT_GREEN = "\033[92m";
    constexpr const char* BRIGHT_YELLOW = "\033[93m";
    constexpr const char* BRIGHT_BLUE = "\033[94m";
    constexpr const char* BRIGHT_MAGENTA = "\033[95m";
    constexpr const char* BRIGHT_CYAN = "\033[96m";
    constexpr const char* BRIGHT_WHITE = "\033[97m";

    inline void Print(const std::string& text, const char* colour)
    {
        std::cout << colour << text << RESET;
    }

    inline const char* GetSymbolColour(char symbol)
    {
        if (symbol == '.')
        {
            return GREEN;
        }
        else if (symbol == '#')
        {
            return BRIGHT_BLACK;
        }
        else if (symbol == 'P')
        {
            return BRIGHT_CYAN;
        }
        else if (symbol == 'F')
        {
            return BRIGHT_YELLOW;
        }
        else if (symbol == 'W')
        {
            return BRIGHT_BLUE;
        }
        else if (symbol == 'S')
        {
            return MAGENTA;
        }
        else if (symbol == 'G')
        {
            return BRIGHT_RED;
        }
        else if (symbol == 'H')
        {
            return YELLOW;
        }
        else if (symbol == 'A')
        {
            return CYAN;
        }
        else if (symbol == 'X')
        {
            return RED;
        }

        return WHITE;
    }

    inline void PrintSymbol(char symbol)
    {
        std::cout << GetSymbolColour(symbol) << symbol << RESET;
    }
}
