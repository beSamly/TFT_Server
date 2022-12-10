#include "pch.h"
#include "InGameMatch.h"
#include "Field.h"
#include "TargetFindUtil.h"

InGameMatch::InGameMatch() {}

void InGameMatch::InitMatch(Field& fieldA, Field& fieldB)
{
    // TODO 일단 PlayerA 의 챔피언은 fieldUid 그대로 옮긴다.
    for (const auto& [fieldUid, champion] : fieldA.GetFieldData()) {
        fieldMap.LocateChampion(fieldUid, champion);
        aChampions.push_back(champion);
    };

    // PlayerB 의 챔피언은 fieldUid를 flip 한 뒤 옮긴다.
    for (const auto& [fieldUid, champion] : fieldB.GetFieldData()) {
        int rowNumber = fieldUid / 10;
        int columnNumber = fieldUid % (rowNumber * 10);

        int rn = 9 - rowNumber;
        int cn = 9 - columnNumber;

        int targetFieldUid = (rn * 10) + cn;

        fieldMap.LocateChampion(targetFieldUid, champion);
        bChampions.push_back(champion);
    };
}

void InGameMatch::Update(float deltaTime)
{
    for (sptr<Champion>& champ : aChampions) {
        UpdateChampion(deltaTime, champ, true);
    }

    for (sptr<Champion>& champ : bChampions) {
        UpdateChampion(deltaTime, champ, false);
    }
}

void InGameMatch::UpdateChampion(float deltaTime, sptr<Champion>& champion, bool isFromA)
{
    // 죽었으면 스킵
    if (champion->state.IsDead()) {
        return;
    }

    champion->transform.Update(deltaTime);
    champion->stat.Update(deltaTime); // expired 된 stat modifier들 제거
    champion->state.Update(deltaTime); // expired 된 state modifier들 제거
    champion->skill.Update(deltaTime);

    //상태값에 관계없이 업데이트 해야하는 컨트롤러들 
    if (champion->skill.IsUsingSkill()) {

    }

    //여전히 이동 중이라면 리턴
    if (champion->transform.IsMoving()) {
        return;
    }

    // 상태불능에 빠져서 스킬을 사용할 수 없다면 리턴
    if (champion->state.IsActionDisabled()) {
        return;
    }

    if (champion->skill.CanUseSkill()) {
        champion->skill.Update(deltaTime);

        // todo
        // skillControoler->update(), skillController.GetReadyOperations
    }
    else {
        //이동 중도 아니고 스킬을(평타,스킬모두) 사용할 수도 없다면 가까운 적이 위치하는 곳으로 1칸 이동하자.
        sptr<Hexagon> currentHexagon = fieldMap.GetHexagonByChampion(champion);
        // Get close enemy position;
        Vector3 targetPosition = TargetFindUtil::FindClosestTragetPosition(currentHexagon->GetPosition(), isFromA ? aChampions : bChampions);
        //Vector3 targetPosition = FindClosestTragetPosition(currentHexagon->GetPosition(), isFromA);
        wptr<Hexagon> nextNode = currentHexagon->GetEmptyNodeTowardDirection(targetPosition);

        if (sptr<Hexagon> nextHexagon = nextNode.lock()) {
            currentHexagon->Release();
            nextHexagon->SetChampion(champion);
            champion->transform.SetTargetPosition(nextHexagon->GetPosition());
        }
    }
}
