#pragma once
#include "TempClientManager.h"
#include "ChampDataFactory.h"

class DataSystem
{
public:
    sptr<TempClientManager> tempClientManager;
    sptr<ChampDataFactory> champDataFactory;

public:
    DataSystem();

    sptr<TempClientManager> GetTempClientManager() { return tempClientManager; }
};
