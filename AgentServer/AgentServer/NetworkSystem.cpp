#include "pch.h"
#include "NetworkSystem.h"
#include "spdlog/spdlog.h"
#include "PacketController.h"
#include "PacketId.h"
#include "Packet.h"

namespace
{
    int32 PORT = 7777;
    int32 MAX_SESSION_COUNT = 100;
} // namespace

NetworkSystem::NetworkSystem()
{
    context = make_shared<asio::io_context>();
    socketServer = make_shared<SocketServer>(context, PORT);
    proxyManager = make_unique<ProxyManager>();
    playerManager = make_unique<PlayerManager>();
    packetController = make_unique<PacketController>();
}

void NetworkSystem::StartSocketServer()
{
    //패킷 컨트롤러 초기화
    packetController->Init();

    // 소켓 서버 실행
    socketServer->OnClientRecv = [&](sptr<ClientSession> client, BYTE* buffer, int len)
    { OnClientRecv(client, buffer, len); };
    socketServer->OnClientDisconnect = [&](sptr<ClientSession> client) { OnClientDisconnect(client); };
    socketServer->OnClientConnect = [&](sptr<ClientSession> client) { OnClientConnect(client); };
    socketServer->StartAccept();
    spdlog::info("Server listening on {}", PORT);
}

void NetworkSystem::HandleIocpEvent(int NETWORK_TIME_OUT_MS)
{
    // socketServer->GetIocpCore()->HandleIocpEvent(NETWORK_TIME_OUT_MS);
}

void NetworkSystem::RunIoContext() { socketServer->RunIoContext(); }

void NetworkSystem::OnClientRecv(sptr<ClientSession> client, BYTE* buffer, int len)
{
    packetController->HandlePacket(client, buffer, len);
}

void NetworkSystem::OnClientDisconnect(sptr<ClientSession> client)
{

    // 로그인 안 한 상태라면 더이상 처리할 필요 없다.
    if (client->GetPlayer() == nullptr)
    {
        return;
    }

    Packet pck((int)PacketId::Prefix::AUTH, (int)PacketId::Auth::LOGOUT_REQ);
    pck.WriteData();
    packetController->HandlePacket(client, pck.GetByteBuffer(), pck.GetSize());
}

void NetworkSystem::OnClientConnect(sptr<ClientSession> client) { playerManager->AddPlayer(client); }
