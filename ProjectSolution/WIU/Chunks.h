#pragma once
#include "Object.h"

//junlong
class Chunks
{
    const static int BoardSize = 10;
    const static int MaxObjects = 6;
    int ObjectCount = 0;

    Object* Objects[MaxObjects];

    char field[BoardSize][BoardSize];
public:
    Chunks();
    void PrintChunk(int chunkNumber);
    void AddObject(Object* obj);
    void RemoveObject(Object* obj);
    Object* GetObject(int index);
    Object* CheckForObject(int x, int y);

    int GetBoardSize();
    int GetMaxObjects();
    int GetObjectCount();
    ~Chunks();
};