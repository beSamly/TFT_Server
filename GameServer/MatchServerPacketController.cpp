#include "pch.h"
#include "MatchServerPacketController.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "PacketId_AG_MT.h"
#include "IPacketController.h"
#include "GameController.h"
#include "PacketId_MT_GM.h"

MatchServerPacketController::MatchServerPacketController(sptr<GameSystem> gameSystem)
{
    //IPacketController::AddController((int)PacketId_AG_MT::Prefix::MATCH, make_shared<CAuthController>(dataSystem->GetPlayerManager()));
    IPacketController::AddController((int)PacketId_MT_GM::Prefix::GAME, make_shared<GameController>(gameSystem));
}

MatchServerPacketController::~MatchServerPacketController() {}
