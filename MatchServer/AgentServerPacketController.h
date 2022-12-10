#pragma once
#include "ClientSession.h"
#include "PacketHeader.h"
#include "SendBuffer.h"
#include "IController.h"
#include "DataSystem.h"
#include "IPacketController.h"
#include "MatchSystem.h"

using std::function;
using std::map;

class AgentServerPacketController : public IPacketController
{
public:
    AgentServerPacketController(sptr<MatchSystem> matchSystem);
    ~AgentServerPacketController();
};
