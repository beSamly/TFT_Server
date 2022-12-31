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
#include "PacketId_AG_MT.h"
#include "PlayerInfo.pb.h"

CAuthController::CAuthController(sptr<PlayerManager> p_playerManager, sptr<ProxyManager> p_proxyMangear)
    : playerManager(p_playerManager), proxyManager(p_proxyMangear)
{
    AddClientHandler((int)PacketId_CL_AG::Auth::LOGIN_REQ, TO_LAMBDA(HandleLoginRequest));
    AddClientHandler((int)PacketId_CL_AG::Auth::LOGOUT_REQ, TO_LAMBDA(HandleLogoutRequest));
}

void CAuthController::HandleLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    Protocol::LoginRequest pkt;
    if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    auto email = pkt.email();
    auto password = pkt.password();
    auto w_email = wstring(email.begin(), email.end());

    // �ش� �̸��Ͽ� ������ ���� ��
    // if (account == nullptr) {
    //	HandleFail(session, "AccountId does not exist");
    //	return;
    //}

    //// ��й�ȣ�� Ʋ�� ��
    // if (wstring(password.begin(), password.end()) != account->GetPassword()) {
    //	HandleFail(session, "Invalid authentication info");
    // }

    // auto accountId = account->GetAccountId();
    // PlayerRef player = MakeShared<Player>(accountId);

    // Player ����

    sptr<Player> player = std::make_shared<Player>();
    session->SetPlayer(player);

    playerManager->AddPlayer(session);

    // Response ������
    Protocol::LoginResponse response;
    response.set_result(true);

    Packet packet((int)PacketId_CL_AG::Prefix::AUTH, (int)PacketId_CL_AG::Auth::LOGIN_RES);
    packet.WriteData<Protocol::LoginResponse>(response);
    session->Send(packet.GetSendBuffer());
}

void CAuthController::HandleLogoutRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    // PlayerManager���� ����
    int playerId = session->GetPlayer()->playerId;
    playerManager->RemovePlayer(playerId);

    // ��Ī ���¶�� MatchSystem�� MatchCancel ��û
    Protocol::PlayerInfo req;
    req.set_playerid(session->GetPlayer()->playerId);

    Packet packet((int)PacketId_AG_MT::Prefix::MATCH, (int)PacketId_AG_MT::Match::MATCH_CANCEL_REQ);
    packet.WriteData<Protocol::PlayerInfo>(req);

    proxyManager->SendToMatchServer(packet.GetSendBuffer());
}