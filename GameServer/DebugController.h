#pragma once

#include "GameSystem.h"
#include "IController.h"

class DebugController : public IController
{
public:
    DebugController(sptr<GameSystem> paramGameSystem);

private:
    sptr<GameSystem> gameSystem;
    void HandleHostCreateReq(sptr<ClientSession>& session, BYTE* buffer, int32 len);
    void HandleGameStartReq(sptr<ClientSession>& session, BYTE* buffer, int32 len);
};
