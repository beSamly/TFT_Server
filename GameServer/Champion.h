#pragma once
#include "TransformController.h"
#include "StatController.h"
#include "SkillController.h"
#include "OperationController.h"
#include "StateController.h"

class Champion
{
public:
    Champion(){};
    int star;
    int uid;
    void Update(float deltaTime); // Champion Ŭ�������� update�ϱ⿣ �ʵ����͵� �ٸ� champ�����͵� ����..

public:
    /* ������ ���� */
    void SetBaseStat(ChampStatData statData) { stat.SetBaseStat(statData); };
    void SetBaseAttackSkill(vector<SkillData> p_skill) { skill.SetBaseAttackSkill(p_skill); }
    void SetSkills(vector<SkillData> p_skill) { skill.SetSkills(p_skill); }

public:
    TransformController transform;
    StatController stat;
    StateController state;
    SkillController skill;
    OperationController operation;
};
