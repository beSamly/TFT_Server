#pragma once
#include "ClientSession.h"
#include "PacketHeader.h"
#include "SendBuffer.h"
#include "IController.h"
#include "DataSystem.h"
#include "IPacketController.h"
#include "GameSystem.h"

using std::function;
using std::map;

class MatchServerPacketController : public IPacketController
{
public:
    MatchServerPacketController(sptr<GameSystem> gameSystem);
    ~MatchServerPacketController();
};
