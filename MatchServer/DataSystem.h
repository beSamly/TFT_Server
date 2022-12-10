#pragma once
#include "TempClientManager.h"

class DataSystem
{
public:
    sptr<TempClientManager> tempClientManager;

public:
    DataSystem();

    sptr<TempClientManager> GetTempClientManager() { return tempClientManager; }
};
