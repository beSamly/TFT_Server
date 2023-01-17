#pragma once
#include "IGameState.h"

class StandByState : public IGameState
{
private:
	int MAX_DURATION_IN_SEC = 10000;
public:
	virtual GameState GetState() override { return GameState::STAND_BY; };
	virtual void Update(GameHost& gameHost, float deltaTime) override;
};
