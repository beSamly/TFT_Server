#include "pch.h"
#include "MatchServerPacketController.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "PacketId_AG_MT.h"
#include "IPacketController.h"
#include "PacketId_MT_GM.h"
#include "HostController.h"

MatchServerPacketController::MatchServerPacketController(sptr<GameSystem> gameSystem)
{
	IPacketController::AddController((int)PacketId_MT_GM::Prefix::HOST, make_shared<HostController>(gameSystem));
}

MatchServerPacketController::~MatchServerPacketController() {}
