#pragma once
#include "ClientSession.h"

class MatchWaitPlayer
{
private:
    bool isMatched = false;

public:
    MatchWaitPlayer();
    wptr<ClientSession> client;
    bool IsMatched() { return isMatched; }
    void SetMatched() { isMatched = true; }
    void SetUnmatched() { isMatched = false; }
};
