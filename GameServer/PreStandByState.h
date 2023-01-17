#pragma once
#include "IGameState.h"

class PreStandByState : public IGameState
{
private:
	int MAX_DURATION_IN_SEC = 2000;
	bool isMatchCreated = false;
	bool isShopRefreshed = false;

public:
	virtual GameState GetState() override { return GameState::PRE_ROUND_START; };
	virtual void Update(GameHost& gameHost, float deltaTime) override;
	void CreateMatch(GameHost& gameHost);
	void RefreshChampShop(GameHost& gameHost);
};
