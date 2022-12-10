#include "pch.h"
#include "CAuthController.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "LoginRequest.pb.h"
#include "LoginResponse.pb.h"
#include "Packet.h"
#include "Player.h"
#include "PlayerManager.h"
#include "PacketId_CL_AG.h"

CAuthController::CAuthController(sptr<PlayerManager> p_playerManager)
{
    playerManager = p_playerManager;

    AddClientHandler((int)Packet_CL_AG::Auth::LOGIN_REQ, TO_LAMBDA(HandleLoginRequest));
    AddClientHandler((int)Packet_CL_AG::Auth::LOGOUT_REQ, TO_LAMBDA(HandleLogoutRequest));
}

void CAuthController::HandleLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    Protocol::LoginRequest pkt;
    if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    auto email = pkt.email();
    auto password = pkt.password();
    auto w_email = wstring(email.begin(), email.end());

    // 해당 이메일에 계정이 없을 때
    // if (account == nullptr) {
    //	HandleFail(session, "AccountId does not exist");
    //	return;
    //}

    //// 비밀번호가 틀릴 때
    // if (wstring(password.begin(), password.end()) != account->GetPassword()) {
    //	HandleFail(session, "Invalid authentication info");
    // }

    // auto accountId = account->GetAccountId();
    // PlayerRef player = MakeShared<Player>(accountId);

    // Player 세팅

    sptr<Player> player = std::make_shared<Player>();
    session->SetPlayer(player);

    playerManager->AddPlayer(session);

    // Response 보내기
    Protocol::LoginResponse response;
    response.set_result(true);

    Packet packet((int)Packet_CL_AG::Prefix::AUTH, (int)Packet_CL_AG::Auth::LOGIN_RES);
    packet.WriteData<Protocol::LoginResponse>(response);
    session->Send(packet.ToSendBuffer());
}

void CAuthController::HandleLogoutRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len) {

    // PlayerManager에서 제거
    int playerId = session->GetPlayer()->playerId;
    playerManager->RemovePlayer(playerId);

    // TODO 매칭 상태라면 MatchSystem에 MatchCancel 요청
    /*sptr<N2M::MatchCancelCommand> command = make_shared<N2M::MatchCancelCommand>(session);
    command->playerId = playerId;
    matchSystem->PushCommand(command);*/
}