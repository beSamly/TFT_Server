#include "pch.h"
#include "MatchServerPacketController.h"

#include "PacketHeader.h"
#include "Login.h"
#include "spdlog/spdlog.h"
#include "PlayerManager.h"
#include "CMatchController.h"
#include "CAuthController.h"
#include "PacketId_CL_AG.h"
#include "IPacketController.h"

MatchServerPacketController::MatchServerPacketController()
{
    /*   IPacketController::AddController((int)Packet_CL_AG::Prefix::AUTH, make_shared<CAuthController>());
       IPacketController::AddController((int)Packet_CL_AG::Prefix::MATCH, make_shared<CMatchController>());*/

    
}

MatchServerPacketController::~MatchServerPacketController() {}
