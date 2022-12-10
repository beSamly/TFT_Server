#pragma once
#include "ClientSession.h"
#include "ProxyManager.h"

#define TO_LAMBDA(FUNC) [&](sptr<ClientSession>& client, BYTE* buffer, int32 len) { FUNC(client, buffer, len); }
#define TO_LAMBDA_FOR_PROXY(FUNC) [&](sptr<Proxy>& client, BYTE* buffer, int32 len) { FUNC(client, buffer, len); }

class IController
{
private:
    map<int, std::function<void(sptr<ClientSession>&, BYTE*, int32)>> clientHandlers;
    map<int, std::function<void(sptr<Proxy>&, BYTE*, int32)>> proxyHandlers;

public:
    void AddClientHandler(int key, function<void(sptr<ClientSession>& client, BYTE* buffer, int32 len)> handler);
    void AddProxyHandler(int key, function<void(sptr<Proxy>& client, BYTE* buffer, int32 len)> handler);

    virtual void HandleClientPacket(sptr<ClientSession>& session, BYTE* buffer, int32 len);
    virtual void HandleProxyPacket(sptr<Proxy>& session, BYTE* buffer, int32 len);
};
