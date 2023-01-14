#include "pch.h"
#include "NetworkSystem.h"
#include "spdlog/spdlog.h"
#include "Packet.h"
#include "ProxyManager.h"
#include "ClientPacketController.h"
#include "ProxyLoginReq.pb.h"
#include "PacketId_Common.h"
#include "PlayerPacketController.h"

namespace
{
    int32 PORT = 5000;
    int32 MAX_SESSION_COUNT = 100;
} // namespace

NetworkSystem::NetworkSystem(sptr<DataSystem> paramDataSystem, sptr<GameSystem> paramGameSystem)
    : dataSystem(paramDataSystem), gameSystem(paramGameSystem)
{
    context = make_shared<asio::io_context>();
    socketServer = make_shared<SocketServer>(context, PORT);
    proxyManager = make_shared<ProxyManager>(SERVER_TYPE::GAME);
    clientPacketController = make_unique<ClientPacketController>(dataSystem, gameSystem, proxyManager);
    playerPacketController = make_unique<PlayerPacketController>(gameSystem);
    matchServerPacketController = make_unique<MatchServerPacketController>(gameSystem);
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
    sptr<ClientSession> clientSession = dynamic_pointer_cast<ClientSession>(client);

    if (!clientSession)
    {
        return;
    }

    if (clientSession->isAuthenticated)
    {
        playerPacketController->HandleClientPacket(clientSession, buffer, len);
    }
    else
    {
        clientPacketController->HandleClientPacket(clientSession, buffer, len);
    }
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
        case SERVER_TYPE::MATCH:
            matchServerPacketController->HandleProxyPacket(session, buffer, len);
            break;

        default:
            // error
            break;
    }
}
