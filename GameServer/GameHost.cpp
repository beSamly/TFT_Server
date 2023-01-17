#include "pch.h"
#include "GameHost.h"
#include "ChampDataFactory.h"
#include "GameStartedState.h"
#include "StandByState.h"
#include "RoundStartedState.h"
#include "PreRoundStartState.h"
#include "PreStandByState.h"
#include "spdlog/spdlog.h"
#include "RoundEndedState.h"

using namespace Command;

namespace
{
#define TO_LAMBDA(FUNC) [&](sptr<ICommand> command) { FUNC(command); }
#define SET_CURRENT_STATE_TO_LAMBDA(FUNC) [&](sptr<IGameState> newState) { FUNC(newState); }
} // namespace

GameHost::GameHost(sptr<ChampDataFactory> paramChampDataFactory, int paramMatchId, vector<int> paramVecPlayerId)
	: champDataFactory(paramChampDataFactory), matchId(paramMatchId), vecPlayerId(paramVecPlayerId)
{
}

void GameHost::Start() { currentState = make_shared<GameStartedState>(); }

bool GameHost::EnterClient(sptr<ClientSession> client)
{
	int playerId = client->GetPlayer()->GetPlayerId();

	bool playerIdExist = false;
	for (int i : vecPlayerId)
	{
		if (i == playerId)
		{
			playerIdExist = true;
		}
	}

	if (!playerIdExist)
	{
		return false;
	}

	sptr<InGamePlayer> inGamePlayer = make_shared<InGamePlayer>();
	inGamePlayer->SetPlayerId(playerId);
	inGamePlayer->SetClientSession(client);
	mapInGamePlayer.emplace(playerId, inGamePlayer);
}

void GameHost::PushCommand(sptr<ICommand> command)
{
	WRITE_LOCK;
	commandQueue.push(command);
}

void GameHost::ProcessCommand()
{
	queue<sptr<ICommand>> copiedCommandQueue;
	{
		WRITE_LOCK;
		copiedCommandQueue = commandQueue;
		commandQueue.empty();
	};

	while (!copiedCommandQueue.empty())
	{
		sptr<ICommand> command = copiedCommandQueue.front();

		gameHostCommandHandler.ProcessCommand(*this, command);

		copiedCommandQueue.pop();
	}
}

void GameHost::Update(float deltaTime)
{
	ProcessCommand();

	if (!currentState) {
		return;
	}

	currentState->Update(*this, deltaTime);

	if (currentState->IsEnded())
	{
		switch (currentState->GetState())
		{
		case GameState::GAME_STARTED:
			spdlog::debug("[GameHost] GAME_STARTED ended. Entering into PreStandByState");
			currentState = make_shared<PreStandByState>();
			break;
		case GameState::PRE_STAND_BY:
			spdlog::debug("[GameHost] PRE_STAND_BY ended. Entering into StandByState");
			currentState = make_shared<StandByState>();
			break;
		case GameState::STAND_BY:
			spdlog::debug("[GameHost] STAND_BY ended. Entering into PreRoundStartState");
			currentState = make_shared<PreRoundStartState>();
			break;
		case GameState::PRE_ROUND_START:
			spdlog::debug("[GameHost] PRE_ROUND_START ended. Entering into RoundStartedState");
			currentState = make_shared<RoundStartedState>();
			break;
		case GameState::ROUND_STARTED:
			spdlog::debug("[GameHost] ROUND_STARTED ended. Entering into RoundEndedState");
			currentState = make_shared<RoundEndedState>();
			break;
		default:
			break;
		}
	}

	// 매치에서 발생한 모든 이벤트 처리
	/*for (sptr<InGameMatch>& match : matchPool.GetMatches() {

	};*/
}

void GameHost::InitChampPool(vector<ChampData> champDataVec)
{
	for (ChampData& data : champDataVec)
	{
		for (int i = 0; i < data.amount; i++)
		{
			data.uid = (data.index * 100000) + i;
			int cost = data.cost;
			champPool[cost].push_back(data);
		}
	}
}
