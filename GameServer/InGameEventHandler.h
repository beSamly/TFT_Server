#pragma once
#include "IInGameEvent.h"

class GameHost;

class InGameEventHandler
{
private:
    map<int, function<void(GameHost& host, sptr<IInGameEvent>)>> handlers;

public:
    InGameEventHandler();
    void ProcessEvent(GameHost& host, sptr<IInGameEvent> event);
private:

};
