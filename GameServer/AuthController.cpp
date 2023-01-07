#include "pch.h"
#include "AuthController.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "LoginRequest.pb.h"
#include "LoginResponse.pb.h"
#include "Packet.h"
#include "Player.h"
#include "PacketId_AG_MT.h"
#include "TempClientManager.h"
#include "PacketId_MT_GM.h"
#include "PacketId_CL_GM.h"
#include "PacketId_Common.h"
#include "ProxyLoginReq.pb.h"
#include "PlayerInfo.pb.h"
#include "GameSystem.h"

AuthController::AuthController(sptr<GameSystem> paramGameSystem, sptr<TempClientManager> paramTempClientManager)
    : gameSystem(paramGameSystem), tempClientManager(paramTempClientManager)
{
    AddClientHandler((int)PacketId_Common::Auth::PROXY_LOGIN_REQ, TO_LAMBDA(HandleProxyLoginRequest));
    AddClientHandler((int)PacketId_Common::Auth::CLIENT_GAME_SERVER_LOGIN_REQ, TO_LAMBDA(HandleLoginRequest));
}

void AuthController::HandleLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    Protocol::PlayerInfo pkt;
    if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    // TODO ��û�� ������ Ŭ���̾�Ʈ�� ���� playerId�� �ش��ϴ� �������� ����
    int playerId = pkt.playerid();

    sptr<Player> player = make_shared<Player>();
    player->playerId = playerId;
    session->SetPlayer(player);
    session->isAuthenticated = true;

    // �ش� �÷��̾ ���� ��Ī�� ���� �������� üũ
    if (sptr<GameHost> gameHost = gameSystem->GetGameHostForPlayer(playerId))
    {
        // TODO ���߿� ������ ���۷����� ���� shared_ptr�� �ٸ� �Լ����� �� ���۷����� ������ ī��Ʈ �����ǳ�?
        int refCountBefore = session.use_count();
        player->SetCurrentGameHost(gameHost);
        bool result = gameHost->EnterClient(session);
        if (!result)
        {

            spdlog::error("[AuthController] can not find game host for playerId = {}", playerId);
        }
        int refCountAfter = session.use_count();
    }
}

void AuthController::HandleProxyLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{

    Protocol::ProxyLoginReq req;
    if (req.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
        return;

    int serverType = req.servertype();
    req.set_servertype((int)SERVER_TYPE::MATCH);

    // TODO ���� ���� �α��� ���� �ʿ�. ����� �����н�
    spdlog::info("[AuthController] Proxy login success for server type {}", serverType);
}
