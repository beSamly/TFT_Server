#pragma once
#include "PlayerManager.h"

class DataSystem
{
public:
    sptr<PlayerManager> playerManager;

public:
    DataSystem();

    sptr<PlayerManager> GetPlayerManager() { return playerManager; }
};
