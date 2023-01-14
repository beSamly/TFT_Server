#include "pch.h"
#include "ClientPacketController.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "PacketId_CL_AG.h"
#include "IPacketController.h"
#include "AuthController.h"
#include "PacketId_MT_GM.h"
#include "PacketId_CL_GM.h"
#include "PacketId_Common.h"
#include "GameSystem.h"

ClientPacketController::ClientPacketController(sptr<DataSystem> dataSystem, sptr<GameSystem> gameSystem, sptr<ProxyManager> proxyManager)
{
    IPacketController::AddController((int)PacketId_Common::Prefix::AUTH,
                                     make_shared<AuthController>(gameSystem, dataSystem->GetTempClientManager(), proxyManager));
}

ClientPacketController::~ClientPacketController() {}
