#pragma once
#include "DataSystem.h"
#include "SocketServer.h"
#include "TempClientManager.h"
#include "MatchServerPacketController.h"
#include "GameSystem.h"
#include "ClientPacketController.h"
#include "PlayerPacketController.h"

class NetworkSystem
{
public:
	NetworkSystem(sptr<DataSystem> paramDataSystem, sptr<GameSystem> paramGameSystem);
	void StartSocketServer();
	void StartProxy();
	void RunProxyIoContext();
	void RunIoContext();
	sptr<ProxyManager> GetProxyManager() { return proxyManager; }

private:
	sptr<DataSystem> dataSystem;
	sptr<GameSystem> gameSystem;
	sptr<SocketServer> socketServer;
	sptr<ProxyManager> proxyManager;

	sptr<MatchServerPacketController> matchServerPacketController;
	sptr<ClientPacketController> clientPacketController;
	sptr<PlayerPacketController> playerPacketController;

	sptr<asio::io_context> context;

private:
	void OnClientAccept(sptr<AsioSession> client);
	void OnClientRecv(sptr<AsioSession> client, BYTE* buffer, int len);
	void OnClientDisconnect(sptr<AsioSession> client);
	void OnProxyConnect(sptr<Proxy> proxy, SERVER_TYPE type);
	void HandleProxyRecv(sptr<Proxy> session, BYTE* buffer, int len);
};
