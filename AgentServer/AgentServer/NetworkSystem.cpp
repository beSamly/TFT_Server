#include "pch.h"
#include "NetworkSystem.h"
#include "spdlog/spdlog.h"

#include "PacketId_CL_AG.h"
#include "Packet.h"
#include "ProxyManager.h"
#include "ClientPacketController.h"
#include "MatchServerPacketController.h"

namespace
{
    int32 PORT = 3000;
    int32 MAX_SESSION_COUNT = 100;
} // namespace

NetworkSystem::NetworkSystem(sptr<DataSystem> p_dataSystem) : dataSystem(p_dataSystem)
{
    context = make_shared<asio::io_context>();
    socketServer = make_shared<SocketServer>(context, PORT);
    proxyManager = make_shared<ProxyManager>();
    // packetController = make_unique<PacketController>();

    clientPacketController = make_unique<ClientPacketController>(dataSystem);
    matchServerPacketController = make_unique<MatchServerPacketController>();
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

    proxyManager->ConnectToMatchServer();
}

void NetworkSystem::RunProxyIoContext() { proxyManager->RunIoContext(); }

void NetworkSystem::RunIoContext() { socketServer->RunIoContext(); }

void NetworkSystem::OnClientAccept(sptr<AsioSession> client)
{
    sptr<ClientSession> clientSession = dynamic_pointer_cast<ClientSession>(client);
    if (!clientSession)
    {
        return;
    }

    dataSystem->GetPlayerManager()->AddPlayer(clientSession);
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
    sptr<ClientSession> clientSession = dynamic_pointer_cast<ClientSession>(client);

    if (!clientSession)
    {
        return;
    }

    // 로그인 안 한 상태라면 더이상 처리할 필요 없다.
    if (clientSession->GetPlayer() == nullptr)
    {
        return;
    }

    Packet pck((int)Packet_CL_AG::Prefix::AUTH, (int)Packet_CL_AG::Auth::LOGOUT_REQ);
    pck.WriteData();
    clientPacketController->HandleClientPacket(clientSession, pck.GetByteBuffer(), pck.GetSize());
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
