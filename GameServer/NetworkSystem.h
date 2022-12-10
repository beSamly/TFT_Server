#pragma once
#include "DataSystem.h"
#include "PacketController.h"
#include "SocketServer.h"

class NetworkSystem
{
public:
	NetworkSystem(sptr<DataSystem> p_dataSystem);
	void StartSocketServer();
	void HandleIocpEvent(int NETWORK_TIME_OUT_MS);
	void RunIoContext();

private:
	sptr<SocketServer> socketServer;
	uptr<PacketController> packetController;
	sptr<asio::io_context> context;
	sptr<DataSystem> dataSystem;


private:
	void OnClientRecv(sptr<ClientSession> client, BYTE* buffer, int len);
	void OnClientDisconnect(sptr<ClientSession> client);
	void OnClientConnect(sptr<ClientSession> client);
};
