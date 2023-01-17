#include "pch.h"
#include "GameStartedState.h"
#include "GameHost.h"

void GameStartedState::Update(GameHost& gameHost, float deltaTime)
{
	elapsedSec += deltaTime;

	if (elapsedSec > 100)
	{

	}

	if (elapsedSec > 1000)
	{
		SetEnded();
	}
}
