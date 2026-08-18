#include "Chunks.h"

Chunks::Chunks()
{
    for (int i = 0; i < 6; i++)
    {
        Objects[i] = nullptr;
    }
}

void Chunks::PrintChunk()
{
    for (int y = 0; y < BoardSize; y++)
    {
        for (int x = 0; x < BoardSize; x++)
        {
            std::cout << field[y][x] << '.';
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