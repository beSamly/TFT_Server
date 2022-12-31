#pragma once
#include "pch.h"
#include "ThreadSystem.h"
#include "NetworkSystem.h"
#include "DataSystem.h"

class ServerApp
{
public:
	sptr<ThreadSystem> threadSystem;
	sptr<MatchSystem> matchSystem;
	sptr<NetworkSystem> networkSystem;
    sptr<DataSystem> dataSystem;

    public:
	ServerApp();

public:
	void StartNetworkSystem();
	void StartMatchSystem();
	void JoinThread() { threadSystem->Join(); };
    void Run();

private:
};
