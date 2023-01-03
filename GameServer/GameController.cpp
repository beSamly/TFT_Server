#include "pch.h"
#include "GameController.h"
#include "GameSystem.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"
#include "PacketId_MT_GM.h"
#include "IController.h"

GameController::GameController(sptr<GameSystem> paramGameSystem) : gameSystem(paramGameSystem)
{
	//AddProxyHandler((int)PacketId_CL_GM::Game::CREATE_HOST_REQ, TO_LAMBDA_FOR_PROXY(HandleCreateHost));
};

void GameController::HandleCreateHost(sptr<Proxy>& session, BYTE* buffer, int32 len) {}