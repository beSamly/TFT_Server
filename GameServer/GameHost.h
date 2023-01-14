#pragma once
#include "pch.h"
#include "Command.h"
#include "ChampDataFactory.h"
#include "InGamePlayer.h"
#include "IGameState.h"
#include "MatchHistory.h"
#include "InGameMatchPool.h"
#include "IInGameEvent.h"
#include "InGameEventHandler.h"
#include "GameHostCommandHandler.h"

using Command::ICommand;

class GameHost
{
private:
    int matchId = 0;
    vector<int> vecPlayerId;
    bool isStarted = false;

public:
    bool IsStarted() { return isStarted; }
    void SetStarted() { isStarted = true; }
    int GetMatchId() { return matchId; }

private:
    USE_LOCK;
    sptr<IGameState> currentState;
    queue<sptr<ICommand>> commandQueue;
    queue<sptr<IInGameEvent>> eventQueue;
    GameHostCommandHandler gameHostCommandHandler;
    InGameEventHandler eventHandler;

    /* Data */
    sptr<ChampDataFactory> champDataFactory;

public:
    map<int, vector<ChampData>> champPool;
    map<int, sptr<InGamePlayer>> inGamePlayerMap;
    MatchHistory matchHistory;
    InGameMatchPool matchPool;

public:
    GameHost(sptr<ChampDataFactory> p_champDataFactory, int matchId, vector<int> paramVecPlayerId);
    void Start();
    bool EnterClient(sptr<ClientSession> client);
    void PushCommand(sptr<ICommand> command);
    void PushEvent(sptr<IInGameEvent> event) { eventQueue.push(event); };
    void Update(float deltaTime);
    void InitChampPool(vector<ChampData> champDataVec);

private:
    void SetCurrentState(sptr<IGameState> newState) { currentState = newState; }
    void ProcessCommand();
};
