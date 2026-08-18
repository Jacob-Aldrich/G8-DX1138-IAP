#include "Chunks.h"
#include <iostream>

Chunks::Chunks()
{
    for (int i = 0; i < 6; i++)
    {
        Objects[i] = nullptr;
    }
}

void Chunks::PrintChunk(int PlayerX, int PlayerY)
{
    for (int y = 0; y < BoardSize; y++)
    {
        for (int x = 0; x < BoardSize; x++)
        {
            if (x == PlayerX && y == PlayerY)
            {
                std::cout << "P ";
            }
            else
            {
                std::cout << field[y][x] << ' ';
            }
        }

        std::cout << '\n';
    }
}

Chunks::~Chunks()
{
    for (int i = 0; i < 6; i++)
    {
        delete Objects[i];
    }
}
