#pragma once
#include "Player.h"
#include "ClientSession.h"

class PlayerManager
{
public:
    PlayerManager();

private:
    USE_LOCK;
    uptr<map<int, sptr<ClientSession>>> clientMap = make_unique<map<int, sptr<ClientSession>>>();
    int tempPlayerId = 1;

public:
    void AddPlayer(sptr<ClientSession> client);
    void RemovePlayer(int playerId);
    void Update();
};
