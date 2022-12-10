#pragma once
#include "InGameMatch.h"

class InGameMatchPool
{
private:
    vector<sptr<InGameMatch>> matchList;

public:
    InGameMatchPool();

    void AddMatch(sptr<InGameMatch> match) { matchList.push_back(match); };
    vector<sptr<InGameMatch>> GetMatches() { return matchList; };
    bool Reset() { matchList.clear(); };
    //void Update(float deltaTime);
};
