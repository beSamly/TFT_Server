#include "pch.h"
#include "DataSystem.h"
#include "PlayerManager.h"

DataSystem::DataSystem()
{
    playerManager = make_shared<PlayerManager>();
    tempClientManager = make_shared<TempClientManager>();
}
