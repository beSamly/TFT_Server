#include "pch.h"
#include "GameServerPacketController.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "PacketId_AG_MT.h"
#include "IPacketController.h"
#include "MatchController.h"

GameServerPacketController::GameServerPacketController(sptr<MatchSystem> matchSystem)
{
	//IPacketController::AddController((int)PacketId_AG_MT::Prefix::MATCH, make_shared<CAuthController>(dataSystem->GetPlayerManager()));
	IPacketController::AddController((int)PacketId_AG_MT::Prefix::MATCH, make_shared<MatchController>(matchSystem));
}

GameServerPacketController::~GameServerPacketController() {}
