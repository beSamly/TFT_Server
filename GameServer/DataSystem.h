#pragma once
#include "PlayerManager.h"
#include "ChampDataFactory.h"

class DataSystem
{
public:
    sptr<PlayerManager> playerManager;
    sptr<ChampDataFactory> champDataFactory;

public:
    DataSystem();

    sptr<PlayerManager> GetPlayerManager() { return playerManager; }
};
