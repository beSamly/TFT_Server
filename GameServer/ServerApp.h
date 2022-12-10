#pragma once
#include "GameSystem.h"
#include "SendBuffer.h"
#include "SocketServer.h"
#include "ThreadSystem.h"
#include "PlayerManager.h"
#include "DataSystem.h"
#include "NetworkSystem.h"

class ServerApp
{
public:
	sptr<ThreadSystem> threadSystem;
	sptr<GameSystem> gameSystem;
	sptr<DataSystem> dataSystem;
	sptr<NetworkSystem> networkSystem;

public:
	ServerApp();

public:
	void StartSocketServer();
	void StartGameSystem();
	void JoinThread() { threadSystem->Join(); };

private:
};
