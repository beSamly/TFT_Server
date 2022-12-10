#pragma once
#include "pch.h"
#include "ClientSession.h"
#include "Champion.h"
#include "ShopProbability.h"
#include "ChampShop.h"
#include "Field.h"
#include "Bench.h"

class InGamePlayer
{
private:
    wptr<ClientSession> client;

public:
    InGamePlayer();

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
