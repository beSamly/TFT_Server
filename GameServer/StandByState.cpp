#include "pch.h"
#include "StandByState.h"

void StandByState::Update(GameHost& gameHost, float deltaTime)
{
	elapsedSec += deltaTime;

	//�ϴ� ������� ���� ���� �ڵ� ������Ʈ ����
	return;
	if (elapsedSec > MAX_DURATION_IN_SEC)
	{
		SetEnded();
	}
}
