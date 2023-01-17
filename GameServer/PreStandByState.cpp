#include "pch.h"
#include "PreStandByState.h"
#include "InGamePlayer.h"
#include "InGameMatch.h"
#include "GameHost.h"

void PreStandByState::Update(GameHost& gameHost, float deltaTime)
{
	elapsedSec += deltaTime;

	// 매칭 생성
	if (!isMatchCreated) {
		CreateMatch(gameHost);
		isMatchCreated = true;
	}

	// 플레이어들의 상점 업데이트
	if (!isShopRefreshed)
	{
		RefreshChampShop(gameHost);
		isShopRefreshed = true;
	}

	if (elapsedSec > MAX_DURATION_IN_SEC)
	{
		SetEnded();
	}
}

void PreStandByState::CreateMatch(GameHost& gameHost)
{
	int playerNumber = gameHost.GetInGamePlayer().size();

	vector<int> playerIdVec;
	for (const auto& [playerId, inGamePlayer] : gameHost.GetInGamePlayer()) {
		playerIdVec.push_back(playerId);
	}

	for (const auto& [playerId, inGamePlayer] : gameHost.GetInGamePlayer()) {

		// 이미 매칭된 상태라면 패스
		if (inGamePlayer->IsMatched()) {
			return;
		}

		int randomId = rand() % playerNumber;

		int targetId = playerIdVec[randomId];

		for (int i = 0; i < playerIdVec.size(); i++) {

			bool matchedBefore = gameHost.matchHistory.IsMatchedBefore(playerId, targetId);
			sptr<InGamePlayer> target = gameHost.GetInGamePlayer()[targetId];

			// 내가 아니고, 만난적이 없고, 상대도 아직 매칭이 안 된 상태라면
			if (!matchedBefore && !target->IsMatched() && playerId != targetId) {
				// 나 매칭 완료
				inGamePlayer->SetMatched(true);

				// 상대 매칭 완료
				target->SetMatched(true);

				int playerAId = inGamePlayer->GetPlayerId();
				int playerBId = target->GetPlayerId();

				// 매칭 리스트에 넣어주기
				sptr<InGameMatch> match = make_shared<InGameMatch>(playerAId, playerBId);
				gameHost.GetMatchPool().AddMatch(match);
				break;
			}

			targetId = (targetId + 1) % playerNumber;

			// 다 돌아봐도 매칭 상대가 없다면? 마지막 target id 인 놈이랑 그냥 매칭해
			if (i == playerIdVec.size()) {
				int playerAId = inGamePlayer->GetPlayerId();
				int playerBId = target->GetPlayerId();

				// 매칭 리스트에 넣어주기
				sptr<InGameMatch> match = make_shared<InGameMatch>(playerAId, playerBId);
				gameHost.GetMatchPool().AddMatch(match);
			}
		}
	}

	// 전투 매치 생성 후에 플래그 값 off
	for (const auto& [playerId, inGamePlayer] : gameHost.GetInGamePlayer()) {
		inGamePlayer->SetMatched(false);
	}
}

void PreStandByState::RefreshChampShop(GameHost& gameHost)
{
	// Champ polling
	map<int, vector<ChampData>> champPool = gameHost.GetChampPool();

	for (const auto& [playerId, inGamePlayer] : gameHost.GetInGamePlayer())
	{
		inGamePlayer->GetChampShop().Clear();
		vector<int> prob = inGamePlayer->GetShopProbability().Poll();

		for (int cost : prob)
		{
			if (!champPool.count(cost))
			{
				continue;
			}

			vector<ChampData>& champByCost = champPool[cost];

			int random = rand() & champByCost.size();
			ChampData data = champByCost[random];

			champByCost.erase(champByCost.begin() + random);
			inGamePlayer->GetChampShop().AddChamp(data.uid, data);
		}
	}
}
