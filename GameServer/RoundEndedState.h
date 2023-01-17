#pragma once
#include "IGameState.h"

class RoundEndedState : public IGameState
{

public:
	virtual GameState GetState() override { return GameState::GAME_STARTED; };
	virtual void Update(GameHost& gameHost, float deltaTime) override;

private:
	int DURATION = 2000;
	bool isMatchReset = false;

private:
	void CreateMatch(GameHost& gameHost);
};
