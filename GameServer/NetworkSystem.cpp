#include "pch.h"
#include "NetworkSystem.h"
#include "DataSystem.h"
#include "spdlog/spdlog.h"
#include "PacketController.h"
#include "PacketId.h"
#include "Packet.h"
#include "TempClientManager.h"

namespace
{
    int32 PORT = 5000;
    int32 MAX_SESSION_COUNT = 100;
} // namespace

NetworkSystem::NetworkSystem(sptr<DataSystem> p_dataSystem) : dataSystem(p_dataSystem)
{
    context = make_shared<asio::io_context>();
    socketServer = make_shared<SocketServer>(context, PORT);
    packetController = make_unique<PacketController>(dataSystem);
    tempClientManager = make_shared<TempClientManager>();
}

void NetworkSystem::StartSocketServer()
{
    //패킷 컨트롤러 초기화
    packetController->Init();

    // 소켓 서버 실행
    socketServer->SetOnAcceptCallback([&](sptr<AsioSession> client) { OnClientAccept(client); });
    socketServer->SetOnClientRecv([&](sptr<AsioSession> client, BYTE* buffer, int len)
                                  { OnClientRecv(client, buffer, len); });
    socketServer->SetOnClientDisconnect([&](sptr<AsioSession> client) { OnClientDisconnect(client); });
    // socketServer->setonclien OnClientConnect = [&](sptr<ClientSession> client) { OnClientConnect(client); };
    socketServer->StartAccept();
    spdlog::info("Server listening on {}", PORT);
}

void NetworkSystem::RunIoContext() { socketServer->RunIoContext(); }

void NetworkSystem::OnClientAccept(sptr<AsioSession> client) {
    spdlog::debug("[NetworkSystem] Client connected");
    tempClientManager->AddClient(client);
    //dataSystem->GetPlayerManager()->AddPlayer(client);
}

void NetworkSystem::OnClientRecv(sptr<AsioSession> client, BYTE* buffer, int len)
{
    sptr<ClientSession> clientSession = dynamic_pointer_cast<ClientSession>(client);

    if (!clientSession)
    {
        return;
    }
    packetController->HandlePacket(clientSession, buffer, len);
}

void NetworkSystem::OnClientDisconnect(sptr<AsioSession> client)
{
    spdlog::debug("[NetworkSystem] Client disconnected");

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

    Packet pck((int)PacketId::Prefix::AUTH, (int)PacketId::Auth::LOGOUT_REQ);
    pck.WriteData();
    packetController->HandlePacket(clientSession, pck.GetByteBuffer(), pck.GetSize());
}
