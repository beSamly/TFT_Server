#include "pch.h"
#include "InGameEventHandler.h"
#include "IInGameEvent.h"



namespace
{
#define TO_LAMBDA(FUNC) [&](sptr<GameHost& host, IInGameEvent> event) { FUNC(host, event); }
} // namespace

InGameEventHandler::InGameEventHandler()
{

}

void InGameEventHandler::ProcessEvent(GameHost& host, sptr<IInGameEvent> event)
{

}
