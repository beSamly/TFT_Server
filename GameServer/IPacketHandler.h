#pragma once
#include "ClientSession.h"

class IPacketHandler
{
public:
    virtual bool RequireLogin() { return true; };
    virtual void HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len) abstract;
    virtual bool Validate(sptr<ClientSession>& session, BYTE* buffer, int32 len) abstract;
};