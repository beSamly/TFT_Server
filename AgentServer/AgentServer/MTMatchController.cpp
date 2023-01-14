#include "pch.h"
#include "MTMatchController.h"
#include "PacketId_CL_AG.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "MatchRequestResponse.pb.h"
#include "Packet.h"
#include "PacketId_AG_MT.h"
#include "MatchRequest.pb.h"
#include "PlayerInfo.pb.h"
#include "MatchCancelResponse.pb.h"
#include "MatchCreatedSend.pb.h"

MTMatchController::MTMatchController(sptr<PlayerManager> p_playerManager) : playerManager(p_playerManager)
{
    AddProxyHandler((int)PacketId_AG_MT::Match::MATCH_REQ_RES, TO_LAMBDA_FOR_PROXY(HandleMatchRes));
    AddProxyHandler((int)PacketId_AG_MT::Match::MATCH_CANCEL_RES, TO_LAMBDA_FOR_PROXY(HandleMatchCancelRes));
    AddProxyHandler((int)PacketId_AG_MT::Match::PENDING_MATCH_CREATED_SEND,
                    TO_LAMBDA_FOR_PROXY(HandlePendingMatchCreatedSend));
    AddProxyHandler((int)PacketId_AG_MT::Match::PENDING_MATCH_CANCELED_SEND,
                    TO_LAMBDA_FOR_PROXY(HandlePendingMatchCanceledSend));
    AddProxyHandler((int)PacketId_AG_MT::Match::MATCH_CREATED_SEND, TO_LAMBDA_FOR_PROXY(HandleMatchCreatedSend));
}

void MTMatchController::HandleMatchRes(sptr<Proxy>& session, BYTE* buffer, int32 len)
{
    Protocol::MatchRequestResponse res;
    if (res.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    // 유저 찾기
    int playerId = res.playerid();
    sptr<ClientSession> client = playerManager->FindPlayer(playerId);
    if (!client)
        return;

    // 유저에게 응답
    Packet packet((int)PacketId_CL_AG::Prefix::MATCH, (int)PacketId_CL_AG::Match::MATCH_REQ_RES);
    packet.WriteData<Protocol::MatchRequestResponse>(res);
    client->Send(packet.GetSendBuffer());
}

void MTMatchController::HandlePendingMatchCreatedSend(sptr<Proxy>& session, BYTE* buffer, int32 len)
{
    Protocol::PlayerInfo res;
    if (res.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    int playerId = res.playerid();

    if (sptr<ClientSession> client = playerManager->FindPlayer(playerId))
    {
        Packet packet((int)PacketId_CL_AG::Prefix::MATCH, (int)PacketId_CL_AG::Match::PENDING_MATCH_CREATED_SEND);
        packet.WriteData();
        client->Send(packet.GetSendBuffer());
    }
    else
    {
        spdlog::debug("[MTMatchController] HandlePendingMatchCreatedSend playerId {} not found", playerId);
    }
}

void MTMatchController::HandlePendingMatchCanceledSend(sptr<Proxy>& session, BYTE* buffer, int32 len)
{
    Protocol::PlayerInfo res;
    if (res.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    int playerId = res.playerid();

    if (sptr<ClientSession> client = playerManager->FindPlayer(playerId))
    {
        Packet packet((int)PacketId_CL_AG::Prefix::MATCH, (int)PacketId_CL_AG::Match::PENDING_MATCH_CANCELED_SEND);
        packet.WriteData();
        client->Send(packet.GetSendBuffer());
    }
    else
    {
        spdlog::debug("[MTMatchController] HandlePendingMatchCanceledSend playerId {} not found", playerId);
    }
}

void MTMatchController::HandleMatchCreatedSend(sptr<Proxy>& session, BYTE* buffer, int32 len)
{
    Protocol::MatchCreatedSend res;
    if (res.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    bool result = res.result();
    int playerId = res.playerid();

    if (sptr<ClientSession> client = playerManager->FindPlayer(playerId))
    {
        Packet packet((int)PacketId_CL_AG::Prefix::MATCH, (int)PacketId_CL_AG::Match::MATCH_CREATED_SEND);
        packet.WriteData<Protocol::MatchCreatedSend>(res);
        client->Send(packet.GetSendBuffer());
    }
    else
    {
        spdlog::debug("[MTMatchController] HandleMatchCreatedSend playerId {} not found", playerId);
    }
}

void MTMatchController::HandleMatchCancelRes(sptr<Proxy>& session, BYTE* buffer, int32 len)
{
    Protocol::MatchCancelResponse resFromMatchServer;
    if (resFromMatchServer.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    int playerId = resFromMatchServer.playerid();
    bool result = resFromMatchServer.result();

    if (sptr<ClientSession> client = playerManager->FindPlayer(playerId))
    {
        Protocol::MatchCancelResponse res;
        res.set_result(result);
        res.set_playerid(playerId);
        Packet packet((int)PacketId_CL_AG::Prefix::MATCH, (int)PacketId_CL_AG::Match::MATCH_CANCEL_RES);
        packet.WriteData<Protocol::MatchCancelResponse>(res);
        client->Send(packet.GetSendBuffer());
        spdlog::debug("HandleMatchCancelRes!! sent reply to client");
    }
    else
    {
        spdlog::debug("[MTMatchController] HandleMatchCancelRes playerId {} not found", playerId);
    }
}
