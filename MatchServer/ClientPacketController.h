#pragma once
#include "ClientSession.h"
#include "PacketHeader.h"
#include "SendBuffer.h"
#include "IController.h"
#include "IPacketController.h"
#include "DataSystem.h"

using std::function;
using std::map;

class ClientPacketController : public IPacketController
{
public:
    ClientPacketController(sptr<DataSystem> dataSystem, sptr<ProxyManager> proxyMangaer);
    ~ClientPacketController();
};
