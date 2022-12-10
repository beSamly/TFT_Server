#include "pch.h"
#include "ShopProbability.h"

ShopProbability::ShopProbability()
{
    // TODO 나중에 하드코딩 제거
    costToProbMap.emplace(1, 12);
    costToProbMap.emplace(2, 17);
    costToProbMap.emplace(3, 30);
    costToProbMap.emplace(4, 20);
    costToProbMap.emplace(5, 10);
    RefreshProb();
    poll.resize(100);
}

void ShopProbability::RefreshProb()
{
    for (auto const& [cost, probability] : costToProbMap)
    {
        for (int i = 0; i <= probability; i++)
        {
            poll.push_back(cost);
        }
    }
}

vector<int> ShopProbability::Poll()
{
    vector<int> returnVec;
    int random = rand() % 100;
    int cost = poll[random];
    returnVec.push_back(cost);
    return returnVec;
}
