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
            fieldMap.emplace((i * 10) + j, nullptr);
        }
    }
}

void Field::Locate(int fieldIndex, sptr<Champion> champ)
{

    if (fieldMap[fieldIndex] != nullptr)
    {
        // Swap
    }
    else
    {
        fieldMap[fieldIndex] = champ;
    }
}

void Field::Remove(int fieldIndex) { fieldMap[fieldIndex] = nullptr; }
