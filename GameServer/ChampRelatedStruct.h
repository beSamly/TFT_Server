#pragma once

struct ChampData
{
    int uid;
    int index;
    string displayName;
    int cost;
    int amount;
};

struct ChampStatData
{
    int star;
    int maxHp;
    int maxMp;
    int attackDamage;
    int abilityPower;
    int armor;
    int magicResistence;
    int attackSpeed;
    int moveSpeed;
};

struct TriggerInfo
{
    string type;
    int threshold;
    int maxTriggerCount;
};

struct OperationTargetCondition
{
    string type;
    int range;
    int targetNumber;
};

struct Operation
{
    string type;
    int value;
    int executeTime;
    int duration;
    OperationTargetCondition condition;
};

struct SkillData
{
    int skillIndex;
    int aniDuration;
    string skillType;
    TriggerInfo triggerInfo;
    vector<Operation> operations;
};


struct ChampSkillData
{
    int championIndex;
    vector<int> baseAttackSkillIndex;
    vector<int> skillIndex;
};
