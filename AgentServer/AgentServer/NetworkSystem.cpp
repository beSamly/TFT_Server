#include "pch.h"
#include "NetworkSystem.h"
#include "spdlog/spdlog.h"

#include "PacketId_CL_AG.h"
#include "Packet.h"
#include "ProxyManager.h"
#include "ClientPacketController.h"
#include "MatchServerPacketController.h"
#include "PacketId_Common.h"
#include "ProxyLoginReq.pb.h"

namespace
{
    int32 PORT = 3000;
    int32 MAX_SESSION_COUNT = 100;
} // namespace

NetworkSystem::NetworkSystem(sptr<DataSystem> p_dataSystem) : dataSystem(p_dataSystem)
{
    context = make_shared<asio::io_context>();
    socketServer = make_shared<SocketServer>(context, PORT);
    proxyManager = make_shared<ProxyManager>(SERVER_TYPE::AGENT);
    // packetController = make_unique<PacketController>();

    clientPacketController = make_unique<ClientPacketController>(dataSystem, proxyManager);
    matchServerPacketController = make_unique<MatchServerPacketController>(dataSystem->GetPlayerManager());
}

void NetworkSystem::StartSocketServer()
{
    // 소켓 서버 실행
    socketServer->SetOnAcceptCallback([&](sptr<AsioSession> client) { OnClientAccept(client); });
    socketServer->SetOnClientRecv([&](sptr<AsioSession> client, BYTE* buffer, int len)
                                  { OnClientRecv(client, buffer, len); });
    socketServer->SetOnClientDisconnect([&](sptr<AsioSession> client) { OnClientDisconnect(client); });
    socketServer->StartAccept();

    spdlog::info("Server listening on {}", PORT);
}

void NetworkSystem::StartProxy()
{
    proxyManager->SetHandleRecv([&](sptr<Proxy> session, BYTE* buffer, int len)
                                { HandleProxyRecv(session, buffer, len); });
    proxyManager->SetOnConnect([&](sptr<Proxy> proxy, SERVER_TYPE type) { OnProxyConnect(proxy, type); });
    proxyManager->ConnectToMatchServer();
}

void NetworkSystem::RunProxyIoContext() { proxyManager->RunIoContext(); }

void NetworkSystem::RunIoContext() { socketServer->RunIoContext(); }

void NetworkSystem::OnClientAccept(sptr<AsioSession> client)
{
    spdlog::info("[NetworkSystem] Client connected");
    sptr<ClientSession> clientSession = dynamic_pointer_cast<ClientSession>(client);
    if (!clientSession)
    {
        return;
    }

    dataSystem->GetTempClientManager()->AddClient(clientSession);
}

void NetworkSystem::OnClientRecv(sptr<AsioSession> client, BYTE* buffer, int len)
{
    sptr<ClientSession> clientSession = dynamic_pointer_cast<ClientSession>(client);

    if (!clientSession)
    {
        return;
    }

    clientPacketController->HandleClientPacket(clientSession, buffer, len);
}

void NetworkSystem::OnClientDisconnect(sptr<AsioSession> client)
{
    spdlog::info("[NetworkSystem] Client disconnected");
    sptr<ClientSession> clientSession = dynamic_pointer_cast<ClientSession>(client);

    if (!clientSession)
    {
        return;
    }

    // 로그인 안 한 상태라면 더이상 처리할 필요 없다.
    sptr<Player> player = clientSession->GetPlayer();
    int playerId = player ? player->playerId : 0;
    if (dataSystem->GetPlayerManager()->FindPlayer(playerId))
    {
        Packet pck((int)PacketId_CL_AG::Prefix::AUTH, (int)PacketId_CL_AG::Auth::LOGOUT_REQ);
        pck.WriteData();
        clientPacketController->HandleClientPacket(clientSession, pck.GetByteBuffer(), pck.GetSize());
    }
}

void NetworkSystem::HandleProxyRecv(sptr<Proxy> client, BYTE* buffer, int len)
{
    switch (client->GetServerType())
    {
        case SERVER_TYPE::MATCH:
            matchServerPacketController->HandleProxyPacket(client, buffer, len);
            break;

        case SERVER_TYPE::GAME:
            break;
        default:
            // error
            break;
    }
}

void NetworkSystem::OnProxyConnect(sptr<Proxy> proxy, SERVER_TYPE type)
{

    spdlog::debug("[NetworkSystem] proxy client connected type = {}", (int)type);

    // 서버 로그인
    Protocol::ProxyLoginReq req;
    req.set_servertype((int)SERVER_TYPE::AGENT);

    Packet packet((int)PacketId_Common::Prefix::AUTH, (int)PacketId_Common::Auth::PROXY_LOGIN_REQ);
    packet.WriteData<Protocol::ProxyLoginReq>(req);
    proxy->Send(packet.GetSendBuffer());
}

void NetworkSystem::Run()
{
   
}