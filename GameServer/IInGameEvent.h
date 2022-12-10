#pragma once
#include "pch.h"

enum InGameEventId
{
    TEST = 1,

};

class IInGameEvent
{
public:
    virtual int GetEventId() abstract;
};

