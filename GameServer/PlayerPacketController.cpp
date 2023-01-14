#include "pch.h"
#include "PlayerPacketController.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "PacketId_CL_AG.h"
#include "IPacketController.h"
#include "AuthController.h"
#include "PacketId_MT_GM.h"
#include "PacketId_CL_GM.h"
#include "GameController.h"

PlayerPacketController::PlayerPacketController(sptr<GameSystem> gameSystem)
{
	IPacketController::AddController((int)PacketId_CL_GM::Prefix::DEBUG, make_shared<GameController>(gameSystem));
	IPacketController::AddController((int)PacketId_CL_GM::Prefix::GAME, make_shared<GameController>(gameSystem));
}

PlayerPacketController::~PlayerPacketController() {}
