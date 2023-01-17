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

AuthController::AuthController(sptr<GameSystem> paramGameSystem, sptr<TempClientManager> paramTempClientManager, sptr<ProxyManager> paramProxyManager)
	: gameSystem(paramGameSystem), tempClientManager(paramTempClientManager), proxyManager(paramProxyManager)
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
	player->SetPlayerId(playerId);
	session->SetPlayer(player);
	session->isAuthenticated = true;

	// �ش� �÷��̾ ���� ��Ī�� ���� �������� üũ
	if (sptr<GameHost> gameHost = gameSystem->GetGameHostByPlayerId(playerId))
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

		// TempClientManager���� ����
		tempClientManager->RemoveClient(session->tempClientId);
	}
	else
	{
		spdlog::error("[AuthController] GameHost not found for player = {}", playerId);
	}
}

void AuthController::HandleProxyLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
	Protocol::ProxyLoginReq req;
	if (req.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	int serverType = req.servertype();

	// ClientSession => Proxy�� ��ȯ �� ProxyManager�� �߰�
	sptr<Proxy> proxy = make_shared<Proxy>(serverType, std::move(session->socket));
	proxy->Start();

	proxyManager->AddProxy(serverType, proxy);

	session->socket.close();

	// TempClientManager���� ����
	tempClientManager->RemoveClient(session->tempClientId);

	// TODO ���� ���� �α��� ���� �ʿ�. ����� �����н�
	spdlog::info("[AuthController] Proxy login success for server type {}", serverType);
}
