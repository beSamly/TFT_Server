#pragma once
#include "IController.h"
#include "PlayerManager.h"
#include "ClientSession.h"

class CAuthController : public IController
{
private:
    sptr<PlayerManager> playerManager;
    sptr<ProxyManager> proxyManager;

public:
    CAuthController(sptr<PlayerManager> p_playerManager, sptr<ProxyManager> p_proxyMangear);

private:
    void HandleLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
    void HandleLogoutRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
};
