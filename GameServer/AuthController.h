#pragma once
#include "IController.h"
#include "ClientSession.h"
#include "TempClientManager.h"

class CAuthController : public IController
{
private:
    sptr<TempClientManager> tempClientManager;

public:
    CAuthController(sptr<TempClientManager> p_tempClientManager);

private:
    void HandleLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
};


class ProxyAuthController : public IController
{
private:
    sptr<TempClientManager> tempClientManager;

public:
    ProxyAuthController(sptr<TempClientManager> p_tempClientManager);

private:
    void HandleLoginRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
};
