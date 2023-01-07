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

    // TODO 요청을 보내온 클라이언트가 실제 playerId에 해당하는 유저인지 검증
    int playerId = pkt.playerid();

    sptr<Player> player = make_shared<Player>();
    player->playerId = playerId;
    session->SetPlayer(player);
    session->isAuthenticated = true;

    // 해당 플레이어가 현재 매칭이 잡힌 유저인지 체크
    if (sptr<GameHost> gameHost = gameSystem->GetGameHostForPlayer(playerId))
    {
        // TODO 나중에 지워라 래퍼런스로 받은 shared_ptr을 다른 함수에서 논 레퍼런스로 받으면 카운트 증가되나?
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

    // TODO 서버 간의 로그인 로직 필요. 현재는 바이패스
    spdlog::info("[AuthController] Proxy login success for server type {}", serverType);
}
