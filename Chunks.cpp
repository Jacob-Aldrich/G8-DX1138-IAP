#include "Chunks.h"

Chunks::Chunks()
{
    for (int i = 0; i < MaxObjects; i++)
    {
        Objects[i] = nullptr;
    }
}

void Chunks::PrintChunk(int chunkNumber)
{
    bool north = false;
    bool east = false;
    bool south = false;
    bool west = false;

    if (chunkNumber == 0)
    {
        north = true;
        east = true;
        south = true;
        west = true;
    }
    else if (chunkNumber == 1)
    {
        south = true;
    }
    else if (chunkNumber == 2)
    {
        west = true;
    }
    else if (chunkNumber == 3)
    {
        north = true;
    }
    else if (chunkNumber == 4)
    {
        east = true;
    }

    // NORTH
    if (north)
        std::cout << "              NORTH\n";
    else
        std::cout << "###############################\n";

    for (int y = 0; y < BoardSize; y++)
    {
        // WEST
        if (y == BoardSize / 2 && west)
            std::cout << "WEST  ";
        else if (west)
            std::cout << "      ";
        else
            std::cout << "##### ";

        // Chunk
        for (int x = 0; x < BoardSize; x++)
        {
            bool objectFound = false;

            for (int i = 0; i < MaxObjects; i++)
            {
                if (Objects[i] != nullptr &&
                    Objects[i]->GetX() == x &&
                    Objects[i]->GetY() == y)
                {
                    std::cout << Objects[i]->GetSymbol() << ' ';
                    objectFound = true;
                    break;
                }
            }

            if (!objectFound)
                std::cout << ". ";
        }

        // EAST
        if (y == BoardSize / 2 && east)
            std::cout << " EAST";
        else if (east)
            std::cout << "     ";
        else
            std::cout << "#####";

        std::cout << '\n';
    }

    // SOUTH
    if (south)
        std::cout << "              SOUTH\n";
    else
        std::cout << "###############################\n";
}

void Chunks::AddObject(Object* obj)
{
    for (int i = 0; i < MaxObjects; i++)
    {
        if (Objects[i] == nullptr)
        {
            Objects[i] = obj;
            ObjectCount++;
            return;
        }
    }
}

void Chunks::RemoveObject(Object* obj)
{
    if (obj == nullptr) {
        return;
    }
    for (int i = 0; i < MaxObjects; i++)
    {
        if (Objects[i] == obj)
        {
            Objects[i] = nullptr;
            ObjectCount--;
            return;
        }
    }
}

Object* Chunks::GetObject(int index)
{
    return Objects[index];
}


Object* Chunks::CheckForObject(int x, int y)
{
    for (int i = 0; i < MaxObjects; i++)
    {
        Object* obj = Objects[i];
        if (obj != nullptr && obj->GetX() == x && obj->GetY() == y)
        {
            return obj;
        }
    }
    return nullptr;
}

int Chunks::GetBoardSize()
{
    return BoardSize;
}

int Chunks::GetMaxObjects()
{
    return MaxObjects;
}

int Chunks::GetObjectCount()
{
    return ObjectCount;
}

Chunks::~Chunks()
{
    for (int i = 0; i < 6; i++)
    {
        delete Objects[i];
    }
}