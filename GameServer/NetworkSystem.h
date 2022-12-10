#pragma once
#include "DataSystem.h"
#include "SocketServer.h"
#include "TempClientManager.h"
#include "MatchServerPacketController.h"
#include "GameSystem.h"
#include "ClientPacketController.h"

class NetworkSystem
{
public:
    NetworkSystem(sptr<DataSystem> p_dataSystem, sptr<GameSystem> p_gameSystem);
    void StartSocketServer();
    void RunIoContext();

private:
    sptr<DataSystem> dataSystem;
    sptr<GameSystem> gameSystem;
    sptr<SocketServer> socketServer;

    sptr<MatchServerPacketController> matchServerPacketController;
    sptr<ClientPacketController> clientPacketController;

    sptr<asio::io_context> context;

private:
    void OnClientAccept(sptr<AsioSession> client);
    void OnClientRecv(sptr<AsioSession> client, BYTE* buffer, int len);
    void OnClientDisconnect(sptr<AsioSession> client);
};
