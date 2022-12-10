#include "pch.h"
#include "ClientPacketController.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "PacketId_CL_AG.h"
#include "IPacketController.h"
#include "AuthController.h"

ClientPacketController::ClientPacketController(sptr<DataSystem> dataSystem)
{
    IPacketController::AddController((int)Packet_CL_AG::Prefix::AUTH, make_shared<AuthController>(dataSystem->GetTempClientManager()));
}

ClientPacketController::~ClientPacketController() {}
