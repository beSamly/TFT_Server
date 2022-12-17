#include "pch.h"
#include "NetworkSystem.h"
#include "spdlog/spdlog.h"
#include "Packet.h"
#include "ProxyManager.h"
#include "ClientPacketController.h"

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
    proxyManager = make_shared<ProxyManager>(SERVER_TYPE::MATCH);
    clientPacketController = make_unique<ClientPacketController>(dataSystem, proxyManager);
}

void NetworkSystem::StartSocketServer()
{
    // ���� ���� ����
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
    // Ŭ���̾�Ʈ�� ���� ������ �������� ���� session��
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

    //// �α��� �� �� ���¶�� ���̻� ó���� �ʿ� ����.
    // if (clientSession->GetPlayer() == nullptr)
    //{
    //     return;
    // }

    // Packet pck((int)PacketId::Prefix::AUTH, (int)PacketId::Auth::LOGOUT_REQ);
    // pck.WriteData();
    // packetController->HandlePacket(clientSession, pck.GetByteBuffer(), pck.GetSize());
}

void NetworkSystem::HandleProxyRecv(sptr<Proxy> session, BYTE* buffer, int len)
{
    switch (session->GetServerType())
    {
        case SERVER_TYPE::AGENT:
            agentServerPacketController->HandleProxyPacket(session, buffer, len);
            break;

        case SERVER_TYPE::GAME:
            break;
        default:
            // error
            break;
    }
}
