#include "pch.h"
#include "RoundEndedState.h"
#include "GameHost.h"

void RoundEndedState::Update(GameHost& gameHost, float deltaTime)
{
	elapsedSec += deltaTime;

	// 전투 매치를 모두 삭제시켜준다.
	if (!isMatchReset) {
		gameHost.GetMatchPool().Reset();
		isMatchReset = true;
	}

	if (DURATION < elapsedSec)
	{
		SetEnded();
	}
}
