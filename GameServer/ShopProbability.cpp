#include "pch.h"
#include "ShopProbability.h"

ShopProbability::ShopProbability()
{
	// TODO 나중에 하드코딩 제거
	mapCostToProbability.emplace(1, 12);
	mapCostToProbability.emplace(2, 17);
	mapCostToProbability.emplace(3, 30);
	mapCostToProbability.emplace(4, 20);
	mapCostToProbability.emplace(5, 10);
	RefreshProb();
	poll.resize(100);
}

void ShopProbability::RefreshProb()
{
	for (auto const& [cost, probability] : mapCostToProbability)
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
