#pragma once
#include "IGameState.h"

class PreRoundStartState : public IGameState
{
private:
	int MAX_DURATION_IN_SEC = 2000;
	bool isBattleFieldInit = false;

public:
	virtual GameState GetState() override { return GameState::PRE_ROUND_START; };
	virtual void Update(GameHost& gameHost, float deltaTime) override;

};
