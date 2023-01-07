#include "pch.h"
#include "HostController.h"
#include "GameSystem.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "PacketId_MT_GM.h"
#include "IController.h"
#include "Command.h"
#include "HostCreateRequest.pb.h"

HostController::HostController(sptr<GameSystem> p_gameSystem) : gameSystem(p_gameSystem)
{
    AddProxyHandler((int)PacketId_MT_GM::Host::HOST_CREATE_REQ, TO_LAMBDA_FOR_PROXY(HandleHostCreate));
};

void HostController::HandleHostCreate(sptr<Proxy>& session, BYTE* buffer, int32 len)
{
    Protocol::HostCreateRequest req;
    if (req.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    vector<int> vecPlayerId;
    for (int i = 0; i < req.playerid_size(); i++)
    {
        vecPlayerId.push_back(req.playerid(i));
    }

    // 게임 시스템에 요청
    sptr<N2G::HostCreateCommand> command = make_shared<N2G::HostCreateCommand>(req.matchid(), vecPlayerId, session);
    gameSystem->PushCommand(command);
}