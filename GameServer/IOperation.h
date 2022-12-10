#pragma once
#include "Champion.h"

class IOperation {

private:
    wptr<Champion> owner;
    wptr<Champion> target;
    int duration = 0;

public:
    void SetOwner(wptr<Champion> champion) { owner = champion; };
    void SetTarget(wptr<Champion> champion) { target = champion; };

public:
    virtual void OnExecute() abstract;
    virtual void OnEnd() abstract;
    virtual void OnTick() abstract;
};