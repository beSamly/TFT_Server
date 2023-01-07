#include "pch.h"
#include "HostController.h"
#include "MatchSystem.h"
#include "PacketHeader.h"
#include "Command.h"
#include "spdlog/spdlog.h"
#include "Packet.h"
#include "PacketId_MT_GM.h"
#include "HostCreateResponse.pb.h"

HostController::HostController(sptr<MatchSystem> p_matchSystem) : matchSystem(p_matchSystem)
{
    AddProxyHandler((int)PacketId_MT_GM::Host::HOST_CREATE_RES, TO_LAMBDA_FOR_PROXY(HandleHostCreateRes));
}

void HostController::HandleHostCreateRes(sptr<Proxy>& proxy, BYTE* buffer, int32 len)
{
    Protocol::HostCreateResponse res;
    if (res.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    bool result = res.result();
    if (result)
    {
        // 매칭 시스템에 알림
        sptr<N2M::HostCreatedCommand> command = make_shared<N2M::HostCreatedCommand>(proxy);
        command->result = res.result();
        command->matchId = res.matchid();
        command->address = res.address();
        command->port = res.port();
        matchSystem->PushCommand(command);
    }
    else
    {
        spdlog::error("[HostController] Failed to create host");
    }
}
