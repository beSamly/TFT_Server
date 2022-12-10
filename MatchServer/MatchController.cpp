#include "pch.h"
#include "MatchController.h"
#include "PacketId_AG_MT.h"
#include "MatchSystem.h"
#include "PacketHeader.h"
#include "Command.h"
#include "spdlog/spdlog.h"
#include "MatchRequestResponse.pb.h"
#include "Packet.h"

MatchController::MatchController(sptr<MatchSystem> p_matchSystem) : matchSystem(p_matchSystem)
{
    handlers[(int)PacketId_AG_MT::Match::MATCH_REQ] = TO_LAMBDA(HandleMatchRequest);
    handlers[(int)PacketId_AG_MT::Match::MATCH_CANCEL_REQ] = TO_LAMBDA(HandleMatchCancelRequest);
}

void MatchController::HandleMatchRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    // 유저에게 응답
    Protocol::MatchRequestResponse response;
    response.set_result(true);

    Packet packet((int)PacketId_AG_MT::Prefix::MATCH, (int)PacketId_AG_MT::Match::MATCH_REQ_RES);
    packet.WriteData<Protocol::MatchRequestResponse>(response);
    session->Send(packet.ToSendBuffer());

    // 매칭 시스템에 요청
    sptr<N2M::MatchRequestCommand> command = make_shared<N2M::MatchRequestCommand>(session);
    matchSystem->PushCommand(command);
}

void MatchController::HandleMatchCancelRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    // 유저에게 응답
    Packet packet((int)PacketId_AG_MT::Prefix::MATCH, (int)PacketId_AG_MT::Match::MATCH_CANCEL_RES);
    packet.WriteData();
    session->Send(packet.ToSendBuffer());

    // 매칭 시스템에 요청
    sptr<N2M::MatchCancelCommand> command = make_shared<N2M::MatchCancelCommand>(session);
    command->playerId = session->GetPlayer()->playerId;
    matchSystem->PushCommand(command);
}
