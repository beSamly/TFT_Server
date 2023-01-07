#pragma once
#include "pch.h"
#include "Champion.h"
#include "ShopProbability.h"
#include "ChampShop.h"
#include "Field.h"
#include "Bench.h"
#include "ClientSession.h"

class InGamePlayer
{
private:
    wptr<ClientSession> client;

public:
    InGamePlayer();
    int playerId;

    ShopProbability shopProb;
    ChampShop champShop;
    Field field;
    Bench bench;
    int gold;

    bool IsMatched() { return isMatched; }
    void SetMatched(bool value) { isMatched = value; }
    void SetClientSession(wptr<ClientSession> p_clinet) { client = p_clinet; }
    void SendToClient();
private:
    bool isMatched;
};
