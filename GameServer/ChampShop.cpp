#include "pch.h"
#include "ChampShop.h"

ChampShop::ChampShop() {}

void ChampShop::AddChamp(int uid, ChampData data) { mapChampData.emplace(uid, data); }

void ChampShop::Remove(int uid) { mapChampData.erase(uid); }

void ChampShop::Clear() { mapChampData.clear(); }

bool ChampShop::Exist(int uid) { return mapChampData.count(uid); }

ChampData ChampShop::Find(int uid)
{
	return mapChampData[uid];
}
