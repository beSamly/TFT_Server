#include "pch.h"
#include "StandByState.h"

void StandByState::Update(GameHost& gameHost, float deltaTime)
{
	elapsedSec += deltaTime;

	//일단 디버깅을 위해 상태 자동 업데이트 끊다
	return;
	if (elapsedSec > MAX_DURATION_IN_SEC)
	{
		SetEnded();
	}
}
