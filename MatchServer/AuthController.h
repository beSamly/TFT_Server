#pragma once
#include "IController.h"
#include "ClientSession.h"
#include "TempClientManager.h"

class AuthController : public IController
{
private:
    sptr<TempClientManager> tempClientManager;
    sptr<ProxyManager> proxyManager;

public:
    AuthController(sptr<TempClientManager> p_tempClientManager, sptr<ProxyManager> p_proxyManager);

private:
    void HandleProxyLoginReq(sptr<ClientSession>& session, BYTE* buffer, int32 len);
};
