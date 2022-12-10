#include "pch.h"
#include "PendingMatch.h"

void PendingMatch::AddPlayer(int playerId, sptr<MatchWaitPlayer> player)
{
    count++;
    acceptStatusMap.emplace(playerId, false);
    playerMap.emplace(playerId, player);
}

void PendingMatch::PlayerAccept(int playerId) { acceptStatusMap[playerId] = true; }

void PendingMatch::PlayerCancel(int playerId)
{
    acceptStatusMap[playerId] = false;
    isCanceled = true;
}

vector<int> PendingMatch::GetPlayerId()
{
    vector<int> playerIds;

    for (const auto& [playerId, isAccepted] : acceptStatusMap)
    {
        playerIds.push_back(playerId);
    }

    return playerIds;
}

bool PendingMatch::IsPlayerAccepted(int playerId) { return acceptStatusMap[playerId]; }

bool PendingMatch::IsReady()
{
    for (const auto& [playerId, isAccepted] : acceptStatusMap)
    {
        if (isAccepted == false)
        {
            return false;
        }
    }

    return true;
}

int PendingMatch::GetMatchId()
{
    // todo
    return 1;
}

void PendingMatch::Update(float deltaTime) { elapsedTime += deltaTime; }
