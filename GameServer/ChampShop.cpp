#include "pch.h"
#include "ChampShop.h"

ChampShop::ChampShop() {}

void ChampShop::AddChamp(int uid, ChampData data) { champMap.emplace(uid, data); }

void ChampShop::Remove(int uid) { champMap.erase(uid); }

void ChampShop::Empty() { champMap.clear(); }

bool ChampShop::Exist(int uid) { return champMap.count(uid); }
