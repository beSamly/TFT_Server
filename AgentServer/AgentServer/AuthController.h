#pragma once
#include "IController.h"
#include "PlayerManager.h"
#include "ClientSession.h"

class AuthController : public IController
{
private:
    map<int, std::function<void(sptr<ClientSession>&, BYTE*, int32)>> handlers;
    sptr<PlayerManager> playerManager;

public:
    AuthController(sptr<PlayerManager> p_playerManager);

    void HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len) override;

private:
    void HandleLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
    void HandleLogoutRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
};
