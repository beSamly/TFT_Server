#pragma once
#include "DataSystem.h"
#include "PacketController.h"
#include "SocketServer.h"
#include "TempClientManager.h"

class NetworkSystem
{
public:
	NetworkSystem(sptr<DataSystem> p_dataSystem);
	void StartSocketServer();
	void RunIoContext();

private:
	sptr<SocketServer> socketServer;
	uptr<PacketController> packetController;
	sptr<asio::io_context> context;
	sptr<DataSystem> dataSystem;
	sptr<TempClientManager> tempClientManager;


private:
	void OnClientAccept(sptr<AsioSession> client);
	void OnClientRecv(sptr<AsioSession> client, BYTE* buffer, int len);
	void OnClientDisconnect(sptr<AsioSession> client);
};
