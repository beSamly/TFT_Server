#include "pch.h"
#include "MatchController.h"
#include "PacketId.h"
#include "MatchSystem.h"
#include "PacketHeader.h"
#include "Command.h"
#include "spdlog/spdlog.h"
#include "MatchRequestResponse.pb.h"
#include "Packet.h"

MatchController::MatchController(sptr<MatchSystem> p_matchSystem)
{
    matchSystem = p_matchSystem;

    handlers[(int)PacketId::Match::MATCH_REQ] = TO_LAMBDA(HandleMatchRequest);
    handlers[(int)PacketId::Match::MATCH_CANCEL_REQ] = TO_LAMBDA(HandleMatchCancelRequest);
}

void MatchController::HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len) {
    PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
    auto packetId = header->id;

    if (handlers[packetId])
    {
        handlers[packetId](session, buffer, len);
    }
    else
    {
        spdlog::error("[MatchController] invalid packetId = {}", packetId);
    }
}

void MatchController::HandleMatchRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    // 유저에게 응답
    Protocol::MatchRequestResponse response;
    response.set_result(true);

    Packet packet((int)PacketId::Prefix::MATCH, (int)PacketId::Match::MATCH_REQ_RES);
    packet.WriteData<Protocol::MatchRequestResponse>(response);
    session->Send(packet.ToSendBuffer());

    // 매칭 시스템에 요청
    sptr<N2M::MatchRequestCommand> command = make_shared<N2M::MatchRequestCommand>(session);
    matchSystem->PushCommand(command);
}

void MatchController::HandleMatchCancelRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    // 유저에게 응답
    Packet packet((int)PacketId::Prefix::MATCH, (int)PacketId::Match::MATCH_CANCEL_RES);
    packet.WriteData();
    session->Send(packet.ToSendBuffer());

    // 매칭 시스템에 요청
    sptr<N2M::MatchCancelCommand> command = make_shared<N2M::MatchCancelCommand>(session);
    command->playerId = session->GetPlayer()->playerId;
    matchSystem->PushCommand(command);
}
