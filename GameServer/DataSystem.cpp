#include "pch.h"
#include "DataSystem.h"

DataSystem::DataSystem()
{
    tempClientManager = make_shared<TempClientManager>();
    champDataFactory = make_shared<ChampDataFactory>();
    champDataFactory->LoadJsonData();
}
