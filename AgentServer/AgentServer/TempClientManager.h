#pragma once
#include "Player.h"
#include "ClientSession.h"

class TempClientManager
{
public:
    TempClientManager();

private:
    USE_LOCK;
    uptr<map<int, sptr<ClientSession>>> clientMap = make_unique<map<int, sptr<ClientSession>>>();
    int tempProxyId = 1;

public:
    void AddClient(sptr<ClientSession> client);
    void RemoveClient(int playerId);
    void Update();
};
