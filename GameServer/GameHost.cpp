#include "pch.h"
#include "GameHost.h"
#include "ChampDataFactory.h"
#include "GameStartedState.h"
#include "StandByState.h"
#include "RoundStartedState.h"

using namespace Command;

namespace
{
#define TO_LAMBDA(FUNC) [&](sptr<ICommand> command) { FUNC(command); }
#define SET_CURRENT_STATE_TO_LAMBDA(FUNC) [&](sptr<IGameState> newState) { FUNC(newState); }
} // namespace

GameHost::GameHost(sptr<ChampDataFactory> p_champDataFactory) : champDataFactory(p_champDataFactory)
{
}

void GameHost::Start() { currentState = make_shared<GameStartedState>(); }

void GameHost::EnterClient(sptr<ClientSession> client)
{
	sptr<InGamePlayer> inGamePlayer = make_shared<InGamePlayer>();
	inGamePlayer->SetClientSession(client);

	int playerId = client->GetPlayer()->playerId;
	inGamePlayerMap.emplace(playerId, inGamePlayer);
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

		commandHandler.ProcessCommand(*this, command);

		copiedCommandQueue.pop();
	}
}

void GameHost::Update(float deltaTime)
{
	ProcessCommand();

	currentState->Update(*this, deltaTime);

	if (currentState->IsEnded())
	{
		switch (currentState->GetState())
		{
		case GameState::GAME_STARTED:
			currentState = make_shared<StandByState>();
			// stand_by 상태로 전환
			break;
		case GameState::STAND_BY:
			currentState = make_shared<RoundStartedState>();
			break;

		case GameState::ROUND_STARTED:
			// currentState = make_shared<RoundEndedState>();

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
		int cost = data.cost;

		if (champPool.find(cost) == champPool.end())
		{
			champPool.emplace(cost, vector<ChampData>());
		}
		else
		{
			champPool[cost].push_back(data);
		}
	}
}
