#include "pch.h"
#include "RoundStartedState.h"
#include "GameHost.h"

void RoundStartedState::Update(GameHost& gameHost, float deltaTime)
{
    elapsedSec += deltaTime;

    if (!isMatchCreated) {
        // round가 시작 되었다면 일단 매칭 생성
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

        // 이미 매칭된 상태라면 패스
        if (inGamePlayer->IsMatched()) {
            return;
        }

        int randomId = rand() % playerNumber;

        int targetId = playerIdVec[randomId];

        for (int i = 0; i < playerIdVec.size(); i++) {

            bool matchedBefore = gameHost.matchHistory.IsMatchedBefore(playerId, targetId);
            sptr<InGamePlayer> target = gameHost.inGamePlayerMap.find(targetId)->second;

            // 내가 아니고, 만난적이 없고, 상대도 아직 매칭이 안 된 상태라면
            if (!matchedBefore && !target->IsMatched() && playerId != targetId) {
                // 나 매칭 완료
                inGamePlayer->SetMatched(true);

                // 상대 매칭 완료
                target->SetMatched(true);

                // 매칭 리스트에 넣어주기
                sptr<InGameMatch> match;
                match->InitMatch(inGamePlayer->field, target->field);
                gameHost.matchPool.AddMatch(match);
                break;
            }

            targetId = (targetId + 1) % playerNumber;


            // 다 돌아봐도 매칭 상대가 없다면? 마지막 target id 인 놈이랑 그냥 매칭해
            if (i == playerIdVec.size()) {
                sptr<InGameMatch> match;
                match->InitMatch(inGamePlayer->field, target->field);
                gameHost.matchPool.AddMatch(match);
            }
        }
    }

}
