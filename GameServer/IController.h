#pragma once
#include "ClientSession.h"

#define TO_LAMBDA(FUNC) [&](sptr<ClientSession>& client, BYTE* buffer, int32 len) { FUNC(client, buffer, len); }

class IController
{
public:
    virtual void HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len) abstract;
};
