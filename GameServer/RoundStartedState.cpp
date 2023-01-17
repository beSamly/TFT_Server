#include "pch.h"
#include "RoundStartedState.h"
#include "GameHost.h"

void RoundStartedState::Update(GameHost& gameHost, float deltaTime)
{
	elapsedSec += deltaTime;

	for (sptr<InGameMatch>& match : gameHost.GetMatchPool().GetMatches()) {
		match->Update(deltaTime);
	}

	// 디버깅 위해서 자동 업데이트 막음
	return;
	if (MAX_DURATION < elapsedSec)
	{
		SetEnded();
	}
}
