#pragma once
#include "Champion.h"

class Field
{
private:
	map<int, sptr<Champion>> mapFieldData;

public:
	Field();
	map<int, sptr<Champion>>& GetFieldData() { return mapFieldData; }
	void Locate(int fieldIndex, sptr<Champion> champ);
	void Remove(int fieldIndex);
	void Remove(sptr<Champion> champion);
	sptr<Champion> FindChampionByUid(int champUid);
};
