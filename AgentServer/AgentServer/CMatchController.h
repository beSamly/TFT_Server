#pragma once
#include "IController.h"

class CMatchController : public IController
{
public:
    CMatchController(sptr<ProxyManager> p_proxyManager);

    sptr<ProxyManager> proxyManager;

private:
    void HandleMatchRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
    void HandleMatchCancelRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
    void HandleMatchAcceptRequest(sptr<ClientSession>& session, BYTE* buffer, int32 len);
};
