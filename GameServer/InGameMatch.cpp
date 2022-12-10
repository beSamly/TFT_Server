#include "pch.h"
#include "InGameMatch.h"
#include "Field.h"
#include "TargetFindUtil.h"

InGameMatch::InGameMatch() {}

void InGameMatch::InitMatch(Field& fieldA, Field& fieldB)
{
    // TODO �ϴ� PlayerA �� è�Ǿ��� fieldUid �״�� �ű��.
    for (const auto& [fieldUid, champion] : fieldA.GetFieldData()) {
        fieldMap.LocateChampion(fieldUid, champion);
        aChampions.push_back(champion);
    };

    // PlayerB �� è�Ǿ��� fieldUid�� flip �� �� �ű��.
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
    // �׾����� ��ŵ
    if (champion->state.IsDead()) {
        return;
    }

    champion->transform.Update(deltaTime);
    champion->stat.Update(deltaTime); // expired �� stat modifier�� ����
    champion->state.Update(deltaTime); // expired �� state modifier�� ����
    champion->skill.Update(deltaTime);

    //���°��� ������� ������Ʈ �ؾ��ϴ� ��Ʈ�ѷ��� 
    if (champion->skill.IsUsingSkill()) {

    }

    //������ �̵� ���̶�� ����
    if (champion->transform.IsMoving()) {
        return;
    }

    // ���ºҴɿ� ������ ��ų�� ����� �� ���ٸ� ����
    if (champion->state.IsActionDisabled()) {
        return;
    }

    if (champion->skill.CanUseSkill()) {
        champion->skill.Update(deltaTime);

        // todo
        // skillControoler->update(), skillController.GetReadyOperations
    }
    else {
        //�̵� �ߵ� �ƴϰ� ��ų��(��Ÿ,��ų���) ����� ���� ���ٸ� ����� ���� ��ġ�ϴ� ������ 1ĭ �̵�����.
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
