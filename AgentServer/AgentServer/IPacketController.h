#pragma once
#include "ClientSession.h"
#include "IController.h"
#include "ProxyManager.h"

class IPacketController
{
private:
    std::map<int, sptr<IController>> controllerMap;

protected:
    void AddController(int prefix, sptr<IController> controller) { controllerMap.emplace(prefix, controller); }

public:
    void virtual HandleClientPacket(sptr<ClientSession>& session, BYTE* buffer, int32 len);
    void virtual HandleProxyPacket(sptr<Proxy>& session, BYTE* buffer, int32 len);
};
