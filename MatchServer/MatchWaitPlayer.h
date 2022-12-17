#pragma once
#include "ClientSession.h"
#include "ProxyManager.h"

class MatchWaitPlayer
{
private:
    bool isMatched = false;
    

public:
    MatchWaitPlayer();
    wptr<Proxy> fromProxy;
    int playerId;
    bool IsMatched() { return isMatched; }
    void SetMatched() { isMatched = true; }
    void SetUnmatched() { isMatched = false; }
};
