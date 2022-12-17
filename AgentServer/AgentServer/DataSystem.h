#pragma once
#include "PlayerManager.h"
#include "TempClientManager.h"

class DataSystem
{
public:
    sptr<PlayerManager> playerManager;
    sptr<TempClientManager> tempClientManager;

public:
    DataSystem();

    sptr<PlayerManager> GetPlayerManager() { return playerManager; }
    sptr<TempClientManager> GetTempClientManager() { return tempClientManager; }
};
