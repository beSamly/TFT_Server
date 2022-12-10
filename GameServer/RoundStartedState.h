#pragma once
#include "IGameState.h"

class RoundStartedState : public IGameState
{

public:
    virtual GameState GetState() override { return GameState::GAME_STARTED; };
    virtual void Update(GameHost& gameHost, float deltaTime) override;

private:
    bool isMatchCreated = false;

private:
    void CreateMatch(GameHost& gameHost);
};
