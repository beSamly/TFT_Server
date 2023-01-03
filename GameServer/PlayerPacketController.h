#pragma once
#include "ClientSession.h"
#include "PacketHeader.h"
#include "SendBuffer.h"
#include "IController.h"
#include "IPacketController.h"
#include "DataSystem.h"
#include "GameSystem.h"

using std::function;
using std::map;

class PlayerPacketController : public IPacketController
{
public:
	PlayerPacketController(sptr<GameSystem> gameSystem);
	~PlayerPacketController();
};
