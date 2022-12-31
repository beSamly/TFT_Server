#include "pch.h"
#include "CMatchController.h"
#include "PacketId_CL_AG.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "MatchRequestResponse.pb.h"
#include "Packet.h"
#include "PacketId_AG_MT.h"
#include "MatchRequest.pb.h"
#include "PlayerInfo.pb.h"

CMatchController::CMatchController(sptr<ProxyManager> p_proxyManager) : proxyManager(p_proxyManager)
{
    AddClientHandler((int)PacketId_CL_AG::Match::MATCH_REQ, TO_LAMBDA(HandleMatchRequest));
    AddClientHandler((int)PacketId_CL_AG::Match::MATCH_CANCEL_REQ, TO_LAMBDA(HandleMatchCancelRequest));
    AddClientHandler((int)PacketId_CL_AG::Match::MATCH_ACCEPT_REQ, TO_LAMBDA(HandleMatchAcceptRequest));
}

void CMatchController::HandleMatchRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    Protocol::PlayerInfo req;
    req.set_playerid(session->GetPlayer()->playerId);

    Packet packet((int)PacketId_AG_MT::Prefix::MATCH, (int)PacketId_AG_MT::Match::MATCH_REQ);
    packet.WriteData<Protocol::PlayerInfo>(req);

    proxyManager->SendToMatchServer(packet.GetSendBuffer());
}

void CMatchController::HandleMatchCancelRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    Protocol::PlayerInfo req;
    req.set_playerid(session->GetPlayer()->playerId);

    Packet packet((int)PacketId_AG_MT::Prefix::MATCH, (int)PacketId_AG_MT::Match::MATCH_CANCEL_REQ);
    packet.WriteData<Protocol::PlayerInfo>(req);

    proxyManager->SendToMatchServer(packet.GetSendBuffer());
}

void CMatchController::HandleMatchAcceptRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len) {
    Protocol::PlayerInfo req;
    req.set_playerid(session->GetPlayer()->playerId);

    Packet packet((int)PacketId_AG_MT::Prefix::MATCH, (int)PacketId_AG_MT::Match::MATCH_ACCEPT_REQ);
    packet.WriteData<Protocol::PlayerInfo>(req);

    proxyManager->SendToMatchServer(packet.GetSendBuffer());
}
