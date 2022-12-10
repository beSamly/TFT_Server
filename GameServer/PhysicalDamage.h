#pragma once
#include "IOperation.h"

class PhysicalDamage : public IOperation
{
public:
    void OnExecute() override;

    void OnEnd() override;

    void OnTick() override;
};

