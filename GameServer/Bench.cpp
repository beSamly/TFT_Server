#include "pch.h"
#include "Bench.h"

Bench::Bench()
{
	// bench data ¼¼ÆÃ
	for (int i = 1; i <= BENCH_COUNT; i++)
	{
		mapBenchData.emplace(i, nullptr);
	}
}

void Bench::Locate(int benchIndex, sptr<Champion> champ)
{
	if (mapBenchData[benchIndex] != nullptr)
	{
		// Swap
	}
	else
	{
		mapBenchData[benchIndex] = champ;
	}
}

void Bench::Remove(int benchIndex) { mapBenchData[benchIndex] = nullptr; }

void Bench::Remove(sptr<Champion> champion)
{
	for (const auto& [benchIndex, champ] : mapBenchData)
	{
		if (champ->GetUid() == champion->GetUid())
		{
			mapBenchData.erase(benchIndex);

		}
	}
}

int Bench::GetEmptyBenchIndex()
{
	for (const auto& [benchIndex, champ] : mapBenchData)
	{
		if (champ == nullptr)
		{
			return benchIndex;
		}
	}

	return 0;
}

sptr<Champion> Bench::FindChampionByUid(int champUid)
{
	for (const auto& [benchIndex, champ] : mapBenchData)
	{
		if (champ->GetUid() == champUid)
		{
			return champ;
		}

	}

	return nullptr;
}
