#pragma once
#include "IPacketHandler.h"
#include "ClientSession.h"
#include "PacketHeader.h"
#include "SendBuffer.h"
#include "IController.h"
#include "PlayerManager.h"
#include "IPacketController.h"

using std::function;
using std::map;

class MatchServerPacketController : public IPacketController
{
public:
    MatchServerPacketController(sptr<PlayerManager> playerManager);
    ~MatchServerPacketController();
};
