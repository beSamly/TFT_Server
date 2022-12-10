#include "pch.h"
#include "Bench.h"

Bench::Bench()
{
    // bench data ¼¼ÆÃ
    int benchCount = 8;

    for (int i = 1; i <= benchCount; i++)
    {
        benchMap.emplace(i, nullptr);
    }
}

void Bench::Locate(int benchIndex, sptr<Champion> champ)
{
    if (benchMap[benchIndex] != nullptr)
    {
        // Swap
    }
    else
    {
        benchMap[benchIndex] = champ;
    }
}

void Bench::Remove(int benchIndex) { benchMap[benchIndex] = nullptr; }

int Bench::GetEmptyBenchIndex()
{
    for (const auto& [benchIndex, champ] : benchMap)
    {
        if (champ == nullptr)
        {
            return benchIndex;
        }
    }

    return 0;
}
