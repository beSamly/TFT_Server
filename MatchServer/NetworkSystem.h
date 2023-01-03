#pragma once
#include "MatchSystem.h"
#include "SocketServer.h"
#include "ProxyManager.h"
#include "AgentServerPacketController.h"
#include "ClientPacketController.h"
#include "GameServerPacketController.h"

class NetworkSystem
{
public:
	NetworkSystem(sptr<DataSystem> dataSystem, sptr<MatchSystem> matchSystem);
	void StartSocketServer();
	void StartProxy();
	void RunProxyIoContext();
	void RunIoContext();
	void Run();
	sptr<ProxyManager> GetProxyManager() { return proxyManager; }

private:
	sptr<DataSystem> dataSystem;
	sptr<SocketServer> socketServer;
	sptr<ProxyManager> proxyManager;
	uptr<AgentServerPacketController> agentServerPacketController;
	uptr<GameServerPacketController> gameServerPacketController;
	uptr<ClientPacketController> clientPacketController;
	sptr<asio::io_context> context;

private:
	void OnClientAccept(sptr<AsioSession> client);
	void OnClientRecv(sptr<AsioSession> client, BYTE* buffer, int len);
	void OnClientDisconnect(sptr<AsioSession> client);
	void OnProxyConnect(sptr<Proxy> proxy, SERVER_TYPE type);
	void HandleProxyRecv(sptr<Proxy> session, BYTE* buffer, int len);
};
