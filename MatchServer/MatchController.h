#pragma once
#include "IController.h"
#include "MatchSystem.h"

class MatchController : public IController
{
private:
    sptr<MatchSystem> matchSystem;

public:
    MatchController(sptr<MatchSystem> matchSystem);

private:
    void HandleMatchReq(sptr<Proxy>& proxy, BYTE* buffer, int32 len);
    void HandleMatchCancelReq(sptr<Proxy>& proxy, BYTE* buffer, int32 len);
    void HandleMatchAcceptReq(sptr<Proxy>& proxy, BYTE* buffer, int32 len);
};
