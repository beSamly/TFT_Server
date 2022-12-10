#pragma once
#include "IGameState.h"

class StandByState : public IGameState
{
public:
    virtual GameState GetState() override { return GameState::STAND_BY; };
    virtual void Update(GameHost& gameHost, float deltaTime) override;
};
