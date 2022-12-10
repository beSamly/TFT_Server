#pragma once
#include "PacketController.h"
#include "SocketServer.h"
#include "ProxyManager.h"

class NetworkSystem
{
public:
    NetworkSystem();
    void StartSocketServer();
    void HandleIocpEvent(int NETWORK_TIME_OUT_MS);
	void RunIoContext();

private:
    sptr<SocketServer> socketServer;
    uptr<PacketController> packetController;
    uptr<ProxyManager> proxyManager;
    uptr<PlayerManager> playerManager;
    sptr<asio::io_context> context;

private:
    void OnClientRecv(sptr<ClientSession> client, BYTE* buffer, int len);
    void OnClientDisconnect(sptr<ClientSession> client);
    void OnClientConnect(sptr<ClientSession> client);
};
