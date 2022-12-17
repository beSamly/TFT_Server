#include "pch.h"
#include "MatchController.h"
#include "PacketId_AG_MT.h"
#include "MatchSystem.h"
#include "PacketHeader.h"
#include "Command.h"
#include "spdlog/spdlog.h"
#include "MatchRequestResponse.pb.h"
#include "Packet.h"
#include "MatchRequest.pb.h"
#include "PlayerInfo.pb.h"

MatchController::MatchController(sptr<MatchSystem> p_matchSystem) : matchSystem(p_matchSystem)
{
    AddProxyHandler((int)PacketId_AG_MT::Match::MATCH_REQ, TO_LAMBDA_FOR_PROXY(HandleMatchReq));
    AddProxyHandler((int)PacketId_AG_MT::Match::MATCH_CANCEL_REQ, TO_LAMBDA_FOR_PROXY(HandleMatchCancelReq));
}

void MatchController::HandleMatchReq(sptr<Proxy>& proxy, BYTE* buffer, int32 len)
{
    Protocol::PlayerInfo pkt;
    if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    int playerId = pkt.playerid();

    // 유저에게 응답
    Protocol::MatchRequestResponse response;
    response.set_result(true);
    response.set_playerid(playerId);

    Packet packet((int)PacketId_AG_MT::Prefix::MATCH, (int)PacketId_AG_MT::Match::MATCH_REQ_RES);
    packet.WriteData<Protocol::MatchRequestResponse>(response);
    proxy->Send(packet.GetSendBuffer());

    // 매칭 시스템에 요청
    sptr<N2M::MatchRequestCommand> command = make_shared<N2M::MatchRequestCommand>(proxy, playerId);
    matchSystem->PushCommand(command);
}

void MatchController::HandleMatchCancelReq(sptr<Proxy>& proxy, BYTE* buffer, int32 len)
{
    Protocol::PlayerInfo pkt;
    if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    int playerId = pkt.playerid();

    // 매칭 시스템에 요청
    sptr<N2M::MatchCancelCommand> command = make_shared<N2M::MatchCancelCommand>(proxy, playerId);
    matchSystem->PushCommand(command);

    // 유저에게 응답
    Packet packet((int)PacketId_AG_MT::Prefix::MATCH, (int)PacketId_AG_MT::Match::MATCH_CANCEL_RES);
    packet.WriteData();
    proxy->Send(packet.GetSendBuffer());
}
