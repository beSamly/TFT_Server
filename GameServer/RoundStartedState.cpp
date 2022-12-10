#include "pch.h"
#include "RoundStartedState.h"
#include "GameHost.h"

void RoundStartedState::Update(GameHost& gameHost, float deltaTime)
{
    elapsedSec += deltaTime;

    if (!isMatchCreated) {
        // round�� ���� �Ǿ��ٸ� �ϴ� ��Ī ����
        CreateMatch(gameHost);
        isMatchCreated = true;
    }

    //gameHost.matchList.Update(deltaTime);

    for (sptr<InGameMatch>& match : gameHost.matchPool.GetMatches()) {
        match->Update(deltaTime);
    }

    if (elapsedSec > 10000)
    {
        SetEnded();
    }
}

void RoundStartedState::CreateMatch(GameHost& gameHost)
{
    int playerNumber = gameHost.inGamePlayerMap.size();

    vector<int> playerIdVec;
    for (const auto& [playerId, inGamePlayer] : gameHost.inGamePlayerMap) {
        playerIdVec.push_back(playerId);
    }

    for (const auto& [playerId, inGamePlayer] : gameHost.inGamePlayerMap) {

        // �̹� ��Ī�� ���¶�� �н�
        if (inGamePlayer->IsMatched()) {
            return;
        }

        int randomId = rand() % playerNumber;

        int targetId = playerIdVec[randomId];

        for (int i = 0; i < playerIdVec.size(); i++) {

            bool matchedBefore = gameHost.matchHistory.IsMatchedBefore(playerId, targetId);
            sptr<InGamePlayer> target = gameHost.inGamePlayerMap.find(targetId)->second;

            // ���� �ƴϰ�, �������� ����, ��뵵 ���� ��Ī�� �� �� ���¶��
            if (!matchedBefore && !target->IsMatched() && playerId != targetId) {
                // �� ��Ī �Ϸ�
                inGamePlayer->SetMatched(true);

                // ��� ��Ī �Ϸ�
                target->SetMatched(true);

                // ��Ī ����Ʈ�� �־��ֱ�
                sptr<InGameMatch> match;
                match->InitMatch(inGamePlayer->field, target->field);
                gameHost.matchPool.AddMatch(match);
                break;
            }

            targetId = (targetId + 1) % playerNumber;


            // �� ���ƺ��� ��Ī ��밡 ���ٸ�? ������ target id �� ���̶� �׳� ��Ī��
            if (i == playerIdVec.size()) {
                sptr<InGameMatch> match;
                match->InitMatch(inGamePlayer->field, target->field);
                gameHost.matchPool.AddMatch(match);
            }
        }
    }

}
