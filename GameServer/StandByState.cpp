#include "pch.h"
#include "StandByState.h"

void StandByState::Update(GameHost& gameHost, float deltaTime)
{
    elapsedSec += deltaTime;

    if (elapsedSec > 1000)
    {
        SetEnded();
    }
}
