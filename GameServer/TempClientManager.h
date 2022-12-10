#pragma once
#include "Player.h"
#include "ClientSession.h"

class TempClientManager
{
public:
    TempClientManager();

private:
    USE_LOCK;
    uptr<map<int, sptr<AsioSession>>> clientMap = make_unique<map<int, sptr<AsioSession>>>();
    int tempPlayerId = 1;

public:
    void AddClient(sptr<AsioSession> client);
    void RemovePlayer(int playerId);
    void Update();
};
