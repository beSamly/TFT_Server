#pragma once

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
    sptr<DataSystem> dataSystem;

public:
    ServerApp();
    ~ServerApp();

public:
    void StartNetworkSystem();
    void JoinThread() { threadSystem->Join(); };

private:
};
