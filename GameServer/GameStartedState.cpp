#include "pch.h"
#include "GameStartedState.h"
#include "GameHost.h"

void GameStartedState::Update(GameHost& gameHost, float deltaTime)
{
    elapsedSec += deltaTime;

    if (elapsedSec > 100)
    {
        // Champ polling

        for (const auto& [playerId, inGamePlayer] : gameHost.inGamePlayerMap)
        {
            vector<int> prob = inGamePlayer->shopProb.Poll();

            for (int cost : prob)
            {
                if (gameHost.champPool.find(cost) != gameHost.champPool.end())
                {
                    vector<ChampData>& champByCost = gameHost.champPool[cost];

                    int random = rand() & champByCost.size();
                    ChampData data = champByCost[random];

                    champByCost.erase(champByCost.begin() + random);
                    inGamePlayer->champShop.AddChamp(data.uid, data);
                }
            }
        }
    }

    if (elapsedSec > 1000)
    {
        SetEnded();
    }
}
