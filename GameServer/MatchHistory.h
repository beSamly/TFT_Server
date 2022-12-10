#pragma once
#include "ChampDataFactory.h"

class MatchHistory
{
private:
    map<int, vector<int>> matchHistoryMap;

public:
    MatchHistory();
    void AddMatchHistory(int playerId, int opponentId);
    bool IsMatchedBefore(int playerId, int opponentId);
    void Reset();

};
