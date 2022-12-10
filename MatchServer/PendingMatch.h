#pragma once
#include "ClientSession.h"
#include "MatchWaitPlayer.h"

class PendingMatch
{
private:
    map<int, sptr<MatchWaitPlayer>> playerMap;
    map<int, bool> acceptStatusMap;
    int count = 0;
    int maxCount = 0;
    bool isCanceled = false;
    int maxElapsedTime = 15;
    int elapsedTime = 0;

public:
    PendingMatch(int playerPerMatch) : maxCount(playerPerMatch) {};
    void AddPlayer(int playerId, sptr<MatchWaitPlayer> player);
    void PlayerAccept(int playerId);
    void PlayerCancel(int playerId);
    vector<int> GetPlayerId();
    map<int, sptr<MatchWaitPlayer>> GetPlayerMap() { return playerMap; };
    bool IsPlayerAccepted(int playerId);
    bool IsFull() { return count == maxCount; }
    bool IsReady();
    bool IsCanceled() { return isCanceled; };
    bool IsExpired() { return elapsedTime >= maxElapsedTime; };
    int GetMatchId();
    void Update(float deltaTime);
};
