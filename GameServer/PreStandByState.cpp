#include "pch.h"
#include "PreStandByState.h"
#include "InGamePlayer.h"
#include "InGameMatch.h"
#include "GameHost.h"

void PreStandByState::Update(GameHost& gameHost, float deltaTime)
{
	elapsedSec += deltaTime;

	// ��Ī ����
	if (!isMatchCreated) {
		CreateMatch(gameHost);
		isMatchCreated = true;
	}

	// �÷��̾���� ���� ������Ʈ
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

		// �̹� ��Ī�� ���¶�� �н�
		if (inGamePlayer->IsMatched()) {
			return;
		}

		int randomId = rand() % playerNumber;

		int targetId = playerIdVec[randomId];

		for (int i = 0; i < playerIdVec.size(); i++) {

			bool matchedBefore = gameHost.matchHistory.IsMatchedBefore(playerId, targetId);
			sptr<InGamePlayer> target = gameHost.GetInGamePlayer()[targetId];

			// ���� �ƴϰ�, �������� ����, ��뵵 ���� ��Ī�� �� �� ���¶��
			if (!matchedBefore && !target->IsMatched() && playerId != targetId) {
				// �� ��Ī �Ϸ�
				inGamePlayer->SetMatched(true);

				// ��� ��Ī �Ϸ�
				target->SetMatched(true);

				int playerAId = inGamePlayer->GetPlayerId();
				int playerBId = target->GetPlayerId();

				// ��Ī ����Ʈ�� �־��ֱ�
				sptr<InGameMatch> match = make_shared<InGameMatch>(playerAId, playerBId);
				gameHost.GetMatchPool().AddMatch(match);
				break;
			}

			targetId = (targetId + 1) % playerNumber;

			// �� ���ƺ��� ��Ī ��밡 ���ٸ�? ������ target id �� ���̶� �׳� ��Ī��
			if (i == playerIdVec.size()) {
				int playerAId = inGamePlayer->GetPlayerId();
				int playerBId = target->GetPlayerId();

				// ��Ī ����Ʈ�� �־��ֱ�
				sptr<InGameMatch> match = make_shared<InGameMatch>(playerAId, playerBId);
				gameHost.GetMatchPool().AddMatch(match);
			}
		}
	}

	// ���� ��ġ ���� �Ŀ� �÷��� �� off
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
