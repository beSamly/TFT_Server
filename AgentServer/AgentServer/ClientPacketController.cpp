#include "pch.h"
#include "ClientPacketController.h"

#include "PacketHeader.h"
#include "Login.h"
#include "spdlog/spdlog.h"
#include "PlayerManager.h"
#include "CMatchController.h"
#include "CAuthController.h"
#include "PacketId_CL_AG.h"
#include "IPacketController.h"

ClientPacketController::ClientPacketController(sptr<DataSystem> dataSystem, sptr<ProxyManager> proxyManager)
{
    IPacketController::AddController((int)PacketId_CL_AG::Prefix::AUTH, make_shared<CAuthController>(dataSystem->GetPlayerManager(), proxyManager));
    IPacketController::AddController((int)PacketId_CL_AG::Prefix::MATCH, make_shared<CMatchController>(proxyManager));

    // PacketController::AddController((int)PacketId_CL_AG::Prefix::IN_GAME, make_shared<CGameController>(matchSystem))

    /* controllerMap.emplace((int)PacketId::Prefix::AUTH,
                           make_shared<AuthController>(dataSystem->GetPlayerManager(), matchSystem));
     controllerMap.emplace((int)PacketId::Prefix::MATCH, make_shared<MatchController>(matchSystem));
     controllerMap.emplace((int)PacketId::Prefix::IN_GAME, make_shared<GameController>());*/
}

ClientPacketController::~ClientPacketController() {}
