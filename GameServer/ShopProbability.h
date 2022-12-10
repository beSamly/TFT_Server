#pragma once

class ShopProbability
{
private:
    vector<int> poll;
    map<int, int> costToProbMap;
    void RefreshProb();

public:
    ShopProbability();

    vector<int> Poll();
    // TransformController
    // StatController
    // SkillController
};
