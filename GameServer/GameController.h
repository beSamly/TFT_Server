#pragma once

#include "GameSystem.h"
#include "IController.h"

class GameController : public IController
{
private:
    map<int, std::function<void(sptr<ClientSession>&, BYTE*, int32)>> handlers;

public:
    GameController();
    void HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len) override;

private:
    void HandleBuy(sptr<ClientSession>& session, BYTE* buffer, int32 len);
};
