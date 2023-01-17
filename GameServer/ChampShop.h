#pragma once
#include "ChampDataFactory.h"

class ChampShop
{
private:
	map<int, ChampData> mapChampData;

public:
	ChampShop();
	void AddChamp(int uid, ChampData data);
	void Remove(int uid);
	void Clear();
	bool Exist(int uid);
	ChampData Find(int uid);
	map<int, ChampData>& GetChampData() { return mapChampData; }
};
