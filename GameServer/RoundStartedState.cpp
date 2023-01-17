#include "pch.h"
#include "RoundStartedState.h"
#include "GameHost.h"

void RoundStartedState::Update(GameHost& gameHost, float deltaTime)
{
	elapsedSec += deltaTime;

	for (sptr<InGameMatch>& match : gameHost.GetMatchPool().GetMatches()) {
		match->Update(deltaTime);
	}

	// ����� ���ؼ� �ڵ� ������Ʈ ����
	return;
	if (MAX_DURATION < elapsedSec)
	{
		SetEnded();
	}
}
