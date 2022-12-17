#pragma once
#include "IPacketHandler.h"
#include "ClientSession.h"
#include "PacketHeader.h"
#include "SendBuffer.h"
#include "IController.h"
#include "PlayerManager.h"
#include "IPacketController.h"
#include "DataSystem.h"
#include "ProxyManager.h"

using std::function;
using std::map;

class ClientPacketController : public IPacketController
{
public:
    ClientPacketController(sptr<DataSystem> dataSystem, sptr<ProxyManager> proxyManager);
    ~ClientPacketController();
};
