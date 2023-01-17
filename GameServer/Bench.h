#pragma once
#include "Champion.h"

class Bench
{
private:
	map<int, sptr<Champion>> mapBenchData;
	int BENCH_COUNT = 8;

public:
	Bench();
	map<int, sptr<Champion>>& GetBenchData() { return mapBenchData; }
	void Locate(int benchIndex, sptr<Champion> champ);
	void Remove(int benchIndex);
	void Remove(sptr<Champion> champion);
	int GetEmptyBenchIndex();
	bool IsEmpty(int benchIndex) { return !mapBenchData.count(benchIndex); };
	sptr<Champion> GetChampionByBenchIndex(int benchIndex) { return mapBenchData.count(benchIndex) ? mapBenchData[benchIndex] : nullptr; }
	sptr<Champion> FindChampionByUid(int champUid);
};
