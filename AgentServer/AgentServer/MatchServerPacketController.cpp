#include "pch.h"
#include "MatchServerPacketController.h"

#include "PacketHeader.h"
#include "Login.h"
#include "spdlog/spdlog.h"
#include "PlayerManager.h"
#include "CMatchController.h"
#include "CAuthController.h"
#include "IPacketController.h"
#include "MTMatchController.h"
#include "PacketId_AG_MT.h"

MatchServerPacketController::MatchServerPacketController(sptr<PlayerManager> playerManager)
{
    IPacketController::AddController((int)PacketId_AG_MT::Prefix::MATCH, make_shared<MTMatchController>(playerManager));
}

MatchServerPacketController::~MatchServerPacketController() {}
