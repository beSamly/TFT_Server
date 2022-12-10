#pragma once
#include "Champion.h"

class Bench
{
private:
    map<int, sptr<Champion>> benchMap;

public:
    Bench();

    void Locate(int benchIndex, sptr<Champion> champ);
    void Remove(int benchIndex);
    int GetEmptyBenchIndex();
};
