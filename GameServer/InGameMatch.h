#pragma once
#include "Field.h"
#include "FieldMap.h"

class InGameMatch
{
public:
	InGameMatch(int aId, int bId) : playerAId(aId), playerBId(bId) { };
	void InitField(Field& playerA, Field& playerB);
	void Update(float deltaTime);

private:
	int playerAId;
	int playerBId;
	FieldMap fieldMap;
	vector <sptr<Champion>> aChampions;
	vector <sptr<Champion>> bChampions;
	// map data

public:
	int GetPlayerAId() { return playerAId; }
	int GetPlayerBId() { return playerBId; }


private:
	void UpdateChampion(float deltaTime, sptr<Champion>& champion, bool isFromA);
};
