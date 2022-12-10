#include "pch.h"
#include "MatchHistory.h"

MatchHistory::MatchHistory() {}

void MatchHistory::AddMatchHistory(int playerId, int opponentId)
{
    matchHistoryMap[playerId].push_back(opponentId);
}

bool MatchHistory::IsMatchedBefore(int playerId, int targetId)
{
    for (int opponentId : matchHistoryMap[playerId]) {
        if (targetId == opponentId) {
            return true;
        }
    }
    return false;
}

void MatchHistory::Reset()
{
    for (const auto& [playerId, opponentVec] : matchHistoryMap) {
        opponentVec.empty();
    }
}


