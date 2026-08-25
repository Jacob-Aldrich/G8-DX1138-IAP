#pragma once

class Game;

class Scenarios
{
    enum ScenarioTypes
    {
        SEND_SOMEONE_EVENT,
        YES_OR_NO_EVENT,
        ITEMS_EVENT,
        CHOOSE_SOMEONE_EVENT,
    };

public:
    Scenarios();
    void ChooseRandomEvent(Game* game);
};
