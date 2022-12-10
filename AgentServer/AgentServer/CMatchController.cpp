#include "pch.h"
#include "CMatchController.h"
#include "PacketId_CL_AG.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "MatchRequestResponse.pb.h"
#include "Packet.h"

CMatchController::CMatchController()
{
    AddClientHandler((int)Packet_CL_AG::Match::MATCH_REQ, TO_LAMBDA(HandleMatchRequest));
    AddClientHandler((int)Packet_CL_AG::Match::MATCH_CANCEL_REQ, TO_LAMBDA(HandleMatchCancelRequest));
}

void CMatchController::HandleMatchRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    // �������� ����
    Protocol::MatchRequestResponse response;
    response.set_result(true);

    Packet packet((int)Packet_CL_AG::Prefix::MATCH, (int)Packet_CL_AG::Match::MATCH_REQ_RES);
    packet.WriteData<Protocol::MatchRequestResponse>(response);
    session->Send(packet.ToSendBuffer());

    // ��Ī �ý��ۿ� ��û
    /*sptr<N2M::MatchRequestCommand> command = make_shared<N2M::MatchRequestCommand>(session);
    matchSystem->PushCommand(command);*/
}

void CMatchController::HandleMatchCancelRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    // �������� ����
    //Packet packet((int)Packet_CL_AG::Prefix::MATCH, (int)Packet_CL_AG::Match::MATCH_CANCEL_RES);
    //packet.WriteData();
    //session->Send(packet.ToSendBuffer());

    //// ��Ī �ý��ۿ� ��û
    //sptr<N2M::MatchCancelCommand> command = make_shared<N2M::MatchCancelCommand>(session);
    //command->playerId = session->GetPlayer()->playerId;
    //matchSystem->PushCommand(command);
}
