#pragma once
#include "pch.h"
#include "ThreadSystem.h"
#include "NetworkSystem.h"

class ServerApp
{
public:
	sptr<ThreadSystem> threadSystem;
	sptr<MatchSystem> matchSystem;
	sptr<NetworkSystem> networkSystem;

public:
	ServerApp();

public:
	void StartSocketServer();
	void StartMatchSystem();
	void JoinThread() { threadSystem->Join(); };

private:
};
