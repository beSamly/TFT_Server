#pragma once
#include "MatchSystem.h"
#include "PacketController.h"
#include "SocketServer.h"

class NetworkSystem
{
public:
	NetworkSystem(sptr<MatchSystem> matchSystem);
	void StartSocketServer();
	void RunIoContext();

private:
	sptr<SocketServer> socketServer;
	uptr<PacketController> packetController;
	sptr<asio::io_context> context;


private:
	void OnClientRecv(sptr<ClientSession> client, BYTE* buffer, int len);
	void OnClientDisconnect(sptr<ClientSession> client);
	void OnClientConnect(sptr<ClientSession> client);
};
