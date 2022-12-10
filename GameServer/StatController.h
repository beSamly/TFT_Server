#pragma once
#include "StatModifier.h"
#include "ChampRelatedStruct.h"

namespace {
    const int MAX_STAT_TYPE = 8;

    enum STAT_TYPE {
        MAX_HP = 0,
        MAX_MP,
        ATTACK_DAMAGE,
        ABILITY_POWER,
        ARMOR,
        MAGIC_RESISTANCE,
        ATTACK_SPEED,
        MOVE_SPEED,
    };
}

class StatController
{
private:
    vector<vector<StatModifier>> modifiers[MAX_STAT_TYPE];
    vector<vector<int>> cashedStat[MAX_STAT_TYPE];

private:
    ChampStatData baseStatData;
    /*int currentHp;
    int currentMp;*/


public:
    /* Stat related */

public:
    StatController() {};
    void SetBaseStat(ChampStatData p_statData) { baseStatData = p_statData; }
    void Update(float deltaTime);
};
