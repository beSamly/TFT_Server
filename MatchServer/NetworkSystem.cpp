#include "pch.h"
#include "NetworkSystem.h"
#include "spdlog/spdlog.h"
#include "Packet.h"
#include "ProxyManager.h"
#include "ClientPacketController.h"
#include "ProxyLoginReq.pb.h"
#include "PacketId_Common.h"

namespace
{
	int32 PORT = 4000;
	int32 MAX_SESSION_COUNT = 100;
} // namespace

NetworkSystem::NetworkSystem(sptr<DataSystem> p_dataSystem, sptr<MatchSystem> matchSystem) : dataSystem(p_dataSystem)
{
	context = make_shared<asio::io_context>();
	socketServer = make_shared<SocketServer>(context, PORT);
	agentServerPacketController = make_unique<AgentServerPacketController>(matchSystem);
	gameServerPacketController = make_unique<GameServerPacketController>(matchSystem);
	proxyManager = make_shared<ProxyManager>(SERVER_TYPE::MATCH);
	clientPacketController = make_unique<ClientPacketController>(dataSystem, proxyManager);
}

void NetworkSystem::StartSocketServer()
{
	// 소켓 서버 실행
	socketServer->SetOnAcceptCallback([&](sptr<AsioSession> client) { OnClientAccept(client); });
	socketServer->SetOnClientRecv([&](sptr<AsioSession> client, BYTE* buffer, int len)
		{ OnClientRecv(client, buffer, len); });
	socketServer->SetOnClientDisconnect([&](sptr<AsioSession> client) { OnClientDisconnect(client); });
	// socketServer->setonclien OnClientConnect = [&](sptr<ClientSession> client) { OnClientConnect(client); };
	socketServer->StartAccept();

	spdlog::info("Server listening on {}", PORT);
}

void NetworkSystem::StartProxy()
{
	proxyManager->SetHandleRecv([&](sptr<Proxy> session, BYTE* buffer, int len)
		{ HandleProxyRecv(session, buffer, len); });
	proxyManager->SetOnConnect([&](sptr<Proxy> proxy, SERVER_TYPE type) { OnProxyConnect(proxy, type); });
	proxyManager->ConnectToGameServer();
}

void NetworkSystem::RunProxyIoContext() { proxyManager->RunIoContext(); }

void NetworkSystem::RunIoContext() { socketServer->RunIoContext(); }

void NetworkSystem::OnClientAccept(sptr<AsioSession> client)
{
	spdlog::debug("[NetworkSystem] Client connected");

	std::shared_ptr<ClientSession> clientSession = dynamic_pointer_cast<ClientSession>(client);
	if (!clientSession)
	{
		return;
	}

	dataSystem->GetTempClientManager()->AddClient(clientSession);
	return;
}

void NetworkSystem::OnClientRecv(sptr<AsioSession> client, BYTE* buffer, int len)
{
	// 클라이언트란 현재 서버로 인증하지 않은 session들
	sptr<ClientSession> clientSession = dynamic_pointer_cast<ClientSession>(client);

	if (!clientSession)
	{
		return;
	}

	clientPacketController->HandleClientPacket(clientSession, buffer, len);
}

void NetworkSystem::OnClientDisconnect(sptr<AsioSession> client)
{
	spdlog::debug("[NetworkSystem] Client disconnected");

	// sptr<ClientSession> clientSession = dynamic_pointer_cast<ClientSession>(client);

	// if (!clientSession)
	//{
	//     return;
	// }

	//// 로그인 안 한 상태라면 더이상 처리할 필요 없다.
	// if (clientSession->GetPlayer() == nullptr)
	//{
	//     return;
	// }

	// Packet pck((int)PacketId::Prefix::AUTH, (int)PacketId::Auth::LOGOUT_REQ);
	// pck.WriteData();
	// packetController->HandlePacket(clientSession, pck.GetByteBuffer(), pck.GetSize());
}

void NetworkSystem::OnProxyConnect(sptr<Proxy> proxy, SERVER_TYPE type)
{
	spdlog::debug("[NetworkSystem] proxy client connected type = {}", (int)type);

	// 서버 로그인
	Protocol::ProxyLoginReq req;
	req.set_servertype((int)SERVER_TYPE::MATCH);

	Packet packet((int)PacketId_Common::Prefix::AUTH, (int)PacketId_Common::Auth::PROXY_LOGIN_REQ);
	packet.WriteData<Protocol::ProxyLoginReq>(req);
	proxy->Send(packet.GetSendBuffer());
}

void NetworkSystem::HandleProxyRecv(sptr<Proxy> session, BYTE* buffer, int len)
{
	switch (session->GetServerType())
	{
	case SERVER_TYPE::AGENT:
		agentServerPacketController->HandleProxyPacket(session, buffer, len);
		break;

	case SERVER_TYPE::GAME:
		gameServerPacketController->HandleProxyPacket(session, buffer, len);
		break;
	default:
		// error
		break;
	}
}
