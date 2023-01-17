#include "pch.h"
#include "DebugController.h"
#include "GameSystem.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "PacketId_MT_GM.h"
#include "IController.h"
#include "PacketId_CL_GM.h"
#include "HostCreateRequest.pb.h"

DebugController::DebugController(sptr<GameSystem> paramGameSystem) : gameSystem(paramGameSystem)
{
	AddClientHandler((int)PacketId_CL_GM::Debug::HOST_CREATE_REQ, TO_LAMBDA(HandleHostCreateReq));
	AddClientHandler((int)PacketId_CL_GM::Debug::GAME_START_REQ, TO_LAMBDA(HandleGameStartReq));
};

void DebugController::HandleHostCreateReq(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
	Protocol::HostCreateRequest req;
	if (req.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
		return;

	vector<int> vecPlayerId;
	for (int i = 0; i < req.playerid_size(); i++)
	{
		vecPlayerId.push_back(req.playerid(i));
	}

	// 게임 시스템에 요청
	//sptr<N2G::HostCreateCommand> command = make_shared<N2G::HostCreateCommand>(req.matchid(), vecPlayerId, session);
	//gameSystem->PushCommand(command);
}

void DebugController::HandleGameStartReq(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
	if (sptr<GameHost> gameHost = session->GetPlayer()->GetCurrentGameHost().lock())
	{
		//gameHost->SetStarted();
	}
	else
	{
		spdlog::error("[DebugController] GameHost is deleted for player {}", session->GetPlayer()->GetPlayerId());
	}
}