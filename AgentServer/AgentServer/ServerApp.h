#pragma once
#include "PacketController.h"
#include "SendBuffer.h"
#include "SocketServer.h"
#include "ThreadSystem.h"
#include "PlayerManager.h"
#include "NetworkSystem.h"

class ServerApp
{
public:
    sptr<ThreadSystem> threadSystem;
    sptr<NetworkSystem> networkSystem;

public:
    ServerApp();

public:
    void StartSocketServer();
    void JoinThread() { threadSystem->Join(); };

private:
};
