#pragma once
#include "IController.h"
#include "PlayerManager.h"

class MTMatchController : public IController
{
public:
    MTMatchController(sptr<PlayerManager> p_playerManager);

    sptr<ProxyManager> proxyManager;
    sptr<PlayerManager> playerManager;

private:
    void HandleMatchRes(sptr<Proxy>& session, BYTE* buffer, int32 len);
    void HandlePendingMatchCreatedSend(sptr<Proxy>& session, BYTE* buffer, int32 len);
    void HandlePendingMatchCanceledSend(sptr<Proxy>& session, BYTE* buffer, int32 len);
    void HandleMatchCreatedSend(sptr<Proxy>& session, BYTE* buffer, int32 len);
    void HandleMatchCancelRes(sptr<Proxy>& session, BYTE* buffer, int32 len);
};
