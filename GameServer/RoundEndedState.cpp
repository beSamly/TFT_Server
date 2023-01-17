#include "pch.h"
#include "RoundEndedState.h"
#include "GameHost.h"

void RoundEndedState::Update(GameHost& gameHost, float deltaTime)
{
	elapsedSec += deltaTime;

	// ���� ��ġ�� ��� ���������ش�.
	if (!isMatchReset) {
		gameHost.GetMatchPool().Reset();
		isMatchReset = true;
	}

	if (DURATION < elapsedSec)
	{
		SetEnded();
	}
}
