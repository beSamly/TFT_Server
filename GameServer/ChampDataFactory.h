#pragma once
#include "pch.h"
#include "ChampRelatedStruct.h"
#include "Champion.h"

class Champion;

class ChampDataFactory
{
private:
    vector<ChampData> champDataVec;
    map<int, vector<ChampStatData>> champStatDataMap;
    map<int, ChampSkillData> champSkillDataMap;
    map<int, SkillData> skillDataMap;

public:
    ChampDataFactory() {};
    void LoadJsonData();
    vector<ChampData> GetChampPoolData();
    ChampStatData GetStatData(int champIndex, int star);
    sptr<Champion> CreateChampion(int champIndexn, int star);


private:
    ChampSkillData GetChampSkillData(int champIndex);
    SkillData GetSkillData(int skillIndex);

private:
    void LoadChampData();
    void LoadChampStatData();
    void LoadSkillData();
    void LoadChampSkillData();
};
