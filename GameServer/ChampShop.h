#pragma once
#include "ChampDataFactory.h"

class ChampShop
{
private:
    map<int, ChampData> champMap;

public:
    ChampShop();
    void AddChamp(int uid, ChampData data);
    void Remove(int uid);
    void Empty();
    bool Exist(int uid);
};
