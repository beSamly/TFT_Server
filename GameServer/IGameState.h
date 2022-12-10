#pragma once
#include "pch.h"

class GameHost;

enum GameState
{
    GAME_STARTED = 1,
    STAND_BY,
    ROUND_STARTED,
    ROUND_ENDED
};

class IGameState
{
private:
    bool isEnded = false;

public:
    float elapsedSec = 0;
    virtual GameState GetState() abstract;
    virtual void Update(GameHost& gameHost, float deltaTime) abstract;
    virtual bool IsEnded() { return isEnded; };
    virtual void SetEnded() { isEnded = true; };
};
