#pragma once
#include "SocketServer.h"
#include "ProxyManager.h"
#include "DataSystem.h"
#include "ClientPacketController.h"
#include "MatchServerPacketController.h"

class NetworkSystem
{
public:
    NetworkSystem(sptr<DataSystem> p_dataSystem);
    void StartSocketServer();
    void StartProxy();
    void RunProxyIoContext();
    void RunIoContext();
    void Run();

private:
    sptr<SocketServer> socketServer;
    uptr<ClientPacketController> clientPacketController;
    uptr<MatchServerPacketController> matchServerPacketController;
    
    sptr<ProxyManager> proxyManager;
    sptr<asio::io_context> context;

    sptr<DataSystem> dataSystem;

private:
    void OnClientAccept(sptr<AsioSession> client);
    void OnClientRecv(sptr<AsioSession> client, BYTE* buffer, int len);
    void OnClientDisconnect(sptr<AsioSession> client);
    void HandleProxyRecv(sptr<Proxy> client, BYTE* buffer, int len);
    void OnProxyConnect(sptr<Proxy> proxy, SERVER_TYPE type);
};
