#include "pch.h"
#include "Field.h"

Field::Field()
{
	// field data ¼¼ÆÃ
	int rowCount = 4;
	int indexCount = 8;

	for (int i = 1; i <= rowCount; i++)
	{
		for (int j = 1; j <= indexCount; j++)
		{
			mapFieldData.emplace((i * 10) + j, nullptr);
		}
	}
}

void Field::Locate(int fieldIndex, sptr<Champion> champ)
{

	if (mapFieldData[fieldIndex] != nullptr)
	{
		// Swap
	}
	else
	{
		mapFieldData[fieldIndex] = champ;
	}
}

void Field::Remove(int fieldIndex) { mapFieldData[fieldIndex] = nullptr; }

void Field::Remove(sptr<Champion> champion)
{
	for (const auto& [fieldIndex, champ] : mapFieldData)
	{
		if (champ->GetUid() == champion->GetUid())
		{
			mapFieldData.erase(fieldIndex);

		}
	}
}

sptr<Champion> Field::FindChampionByUid(int champUid)
{
	for (const auto& [fieldIndex, champ] : mapFieldData)
	{
		if (champ->GetUid() == champUid)
		{
			return champ;
		}

	}

	return nullptr;
}
