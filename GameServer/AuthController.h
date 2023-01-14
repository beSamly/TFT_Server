#pragma once
#include "IController.h"
#include "ClientSession.h"
#include "TempClientManager.h"
#include "GameSystem.h"

class AuthController : public IController
{
private:
    sptr<TempClientManager> tempClientManager;
    sptr<GameSystem> gameSystem;
    sptr<ProxyManager> proxyManager;

public:
    AuthController(sptr<GameSystem> paramGameSystem, sptr<TempClientManager> paramTempClientManager, sptr<ProxyManager> paramProxyManager);

private:
    void HandleLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
    void HandleProxyLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
};
