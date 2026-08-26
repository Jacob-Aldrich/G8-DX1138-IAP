#pragma once
#include "Entity.h"

class Skinwalker : public Entity
{
public:
    Skinwalker(std::string name = "Stranger");
    virtual void dialogue();
};

namespace skinwalkerjumpscare
{
    void ShowSkinwalkerJumpscare();
}
