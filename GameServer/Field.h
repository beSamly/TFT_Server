#pragma once
#include "Champion.h"

class Field
{
private:
    map<int, sptr<Champion>> fieldMap;

public:
    Field();
    void Locate(int fieldIndex, sptr<Champion> champ);
    void Remove(int fieldIndex);
    map<int, sptr<Champion>> GetFieldData() { return fieldMap; };
};
