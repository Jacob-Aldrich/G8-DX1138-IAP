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

    void RunSendSomeoneEvent(Game* game);
    void RunYesOrNoEvent(Game* game);
    void RunItemsEvent(Game* game);
    void RunChooseSomeoneEvent(Game* game);
    void StartHouseAttackCombat(Game* game, bool skinwalkerAttack);

public:
    Scenarios();
    void ChooseRandomEvent(Game* game);
};
