#include "pch.h"
#include "PacketController.h"
#include "PacketHeader.h"
#include "PacketId.h"
#include "spdlog/spdlog.h"
#include "MatchController.h"
//#include "AuthController.h"
#include "PlayerManager.h"
#include "MatchSystem.h"

PacketController::PacketController(sptr<MatchSystem> matchSystem)
{
	//controllerMap.emplace((int)PacketId::Prefix::AUTH,
		//make_shared<AuthController>(dataSystem->GetPlayerManager(), matchSystem));
	//controllerMap.emplace((int)PacketId::Prefix::MATCH, make_shared<MatchController>(matchSystem));
	//controllerMap.emplace((int)PacketId::Prefix::IN_GAME, make_shared<GameController>());
}

PacketController::~PacketController() {}

void PacketController::Init() {}

void PacketController::HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{

	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	auto prefix = header->prefix;

	sptr<IController> controller = controllerMap[prefix];

	if (controller)
	{
		controller->HandlePacket(session, buffer, len);
	}
	else
	{
		spdlog::error("[PacketController] invalid prefix = {}", prefix);
	}
}