#include "pch.h"
#include "ClientPacketController.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "PacketId_Common.h"
#include "IPacketController.h"
#include "AuthController.h"

ClientPacketController::ClientPacketController(sptr<DataSystem> dataSystem, sptr<ProxyManager> proxyManager)
{
    IPacketController::AddController((int)PacketId_Common::Prefix::AUTH,
                                     make_shared<AuthController>(dataSystem->GetTempClientManager(), proxyManager));
}

ClientPacketController::~ClientPacketController() {}
