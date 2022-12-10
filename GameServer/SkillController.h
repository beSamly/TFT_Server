#pragma once
#include "Vector3.h"
#include "ChampRelatedStruct.h"

class SkillController
{
public:
    SkillController() {};
    void Update(float deltaTime);
    bool IsUsingSkill();
    bool CanUseSkill();

public:
    /* 데이터 세팅 */
    void SetBaseAttackSkill(vector<SkillData> p_skill) { baseAttack = p_skill; }
    void SetSkills(vector<SkillData> p_skill) { skills = p_skill; }

private:

    vector<SkillData> baseAttack;
    vector<SkillData> skills;
};
