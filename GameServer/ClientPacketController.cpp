#include "pch.h"
#include "ClientPacketController.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "PacketId_CL_AG.h"
#include "IPacketController.h"
#include "AuthController.h"
#include "PacketId_MT_GM.h"
#include "PacketId_CL_GM.h"

ClientPacketController::ClientPacketController(sptr<DataSystem> dataSystem)
{
	IPacketController::AddController((int)PacketId_Common::Prefix::AUTH, make_shared<AuthController>(dataSystem->GetTempClientManager()));
}

ClientPacketController::~ClientPacketController() {}
