#pragma once
#include "Field.h"
#include "FieldMap.h"

class InGameMatch
{
public:
    InGameMatch();
    void InitMatch(Field& playerA, Field& playerB);
    void Update(float deltaTime);

    FieldMap fieldMap;
    vector <sptr<Champion>> aChampions;
    vector <sptr<Champion>> bChampions;
    // map data

private:
    void UpdateChampion(float deltaTime, sptr<Champion>& champion, bool isFromA);
};
