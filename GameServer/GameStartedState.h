#pragma once
#include "IGameState.h"
#include "GameHost.h"

class GameStartedState : public IGameState
{

public:
    virtual GameState GetState() override { return GameState::GAME_STARTED; };
    virtual void Update(GameHost& gameHost, float deltaTime) override;
};
