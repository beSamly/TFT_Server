#include "pch.h"
#include "DataSystem.h"
#include "PlayerManager.h"

DataSystem::DataSystem()
{
    playerManager = make_shared<PlayerManager>();

    champDataFactory = make_shared<ChampDataFactory>();
    champDataFactory->LoadJsonData();
}
