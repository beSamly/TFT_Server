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
#include "MatchCancelResponse.pb.h"

MatchController::MatchController(sptr<MatchSystem> p_matchSystem) : matchSystem(p_matchSystem)
{
    AddProxyHandler((int)PacketId_AG_MT::Match::MATCH_REQ, TO_LAMBDA_FOR_PROXY(HandleMatchReq));
    AddProxyHandler((int)PacketId_AG_MT::Match::MATCH_CANCEL_REQ, TO_LAMBDA_FOR_PROXY(HandleMatchCancelReq));
    AddProxyHandler((int)PacketId_AG_MT::Match::MATCH_ACCEPT_REQ, TO_LAMBDA_FOR_PROXY(HandleMatchAcceptReq));
}

void MatchController::HandleMatchReq(sptr<Proxy>& proxy, BYTE* buffer, int32 len)
{
    Protocol::PlayerInfo pkt;
    if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    int playerId = pkt.playerid();

    // �������� ����
    Protocol::MatchRequestResponse response;
    response.set_result(true);
    response.set_playerid(playerId);

    Packet packet((int)PacketId_AG_MT::Prefix::MATCH, (int)PacketId_AG_MT::Match::MATCH_REQ_RES);
    packet.WriteData<Protocol::MatchRequestResponse>(response);
    proxy->Send(packet.GetSendBuffer());

    // ��Ī �ý��ۿ� ��û
    sptr<N2M::MatchRequestCommand> command = make_shared<N2M::MatchRequestCommand>(proxy, playerId);
    matchSystem->PushCommand(command);
}

void MatchController::HandleMatchCancelReq(sptr<Proxy>& proxy, BYTE* buffer, int32 len)
{
    Protocol::PlayerInfo pkt;
    if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    int playerId = pkt.playerid();

    // ��Ī �ý��ۿ� ��û
    sptr<N2M::MatchCancelCommand> command = make_shared<N2M::MatchCancelCommand>(proxy, playerId);
    matchSystem->PushCommand(command);

     // �������� ���� todo MatchSystem���� ������ ������ �Ŀ� ������ ����� �� ����.
    Protocol::MatchCancelResponse res;
    res.set_result(true);
    res.set_playerid(playerId);

    Packet packet((int)PacketId_AG_MT::Prefix::MATCH, (int)PacketId_AG_MT::Match::MATCH_CANCEL_RES);
    packet.WriteData<Protocol::MatchCancelResponse>(res);
    proxy->Send(packet.GetSendBuffer());
}

void MatchController::HandleMatchAcceptReq(sptr<Proxy>& proxy, BYTE* buffer, int32 len) {
    Protocol::PlayerInfo pkt;
    if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    int playerId = pkt.playerid();

    // ��Ī �ý��ۿ� ��û
    sptr<N2M::MatchAcceptCommand> command = make_shared<N2M::MatchAcceptCommand>(proxy, playerId);
    matchSystem->PushCommand(command);
}
