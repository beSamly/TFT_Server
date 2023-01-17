#include "pch.h"
#include "PreRoundStartState.h"
#include "InGamePlayer.h"
#include "InGameMatch.h"
#include "GameHost.h"

void PreRoundStartState::Update(GameHost& gameHost, float deltaTime)
{
	elapsedSec += deltaTime;

	// 챔피언들을 전투 필드에 위치시켜준다.
	if (!isBattleFieldInit)
	{
		vector<sptr<InGameMatch>>& vecMatch = gameHost.GetMatchPool().GetMatches();

		for (sptr<InGameMatch>& match : vecMatch) {
			int playerAId = match->GetPlayerAId();
			int playerBId = match->GetPlayerBId();

			sptr<InGamePlayer> playerA = gameHost.FindInGamePlayer(playerAId);
			sptr<InGamePlayer> playerB = gameHost.FindInGamePlayer(playerBId);

			match->InitField(playerA->GetField(), playerB->GetField());
		}

		isBattleFieldInit = true;
	}


	if (elapsedSec > MAX_DURATION_IN_SEC)
	{
		SetEnded();
	}
}
