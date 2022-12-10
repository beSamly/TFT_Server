#pragma once
#include "IController.h"
#include "MatchSystem.h"

class MatchController : public IController
{
private:
    map<int, std::function<void(sptr<ClientSession>&, BYTE*, int32)>> handlers;
    sptr<MatchSystem> matchSystem;

public:
    MatchController(sptr<MatchSystem> matchSystem);

private:
    void HandleMatchRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
    void HandleMatchCancelRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
};
