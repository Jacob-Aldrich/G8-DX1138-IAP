#pragma once
#include "Object.h"

class Chunks
{
    const static int BoardSize = 10;
    Object* Objects[6];

    char field[BoardSize][BoardSize];
public:
    Chunks();

    void PrintChunk();
    ~Chunks();
};