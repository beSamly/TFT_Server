#pragma once

class StatModifier
{
private:
    int addValue;
    int multiplyValue;
    int durationTime;
public:
    StatModifier();
    void SetAddValue(int value) { addValue = value; };
    void SetMultiplyValue(int value) { multiplyValue = value; };
};
