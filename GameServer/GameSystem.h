#pragma once
#include "GameHost.h"
#include "Command.h"
#include "DataSystem.h"

using namespace Command;

class GameSystem
{
public:
    GameSystem(sptr<DataSystem> p_dataSystem);

public:
    void Run();
    void PushCommand(sptr<ICommand> command);

private:
    USE_LOCK;
    int hostId = 1; // temp
    map<int, sptr<GameHost>> gameHostMap;

    /* Command related */
    queue<sptr<ICommand>> commandQueue;
    map<int, function<void(sptr<ICommand>)>> commandHandler;

    /* GameData related */
    sptr<DataSystem> dataSystem;

private:
    void Update(float deltaTime);

    /* Command related */
    queue<sptr<ICommand>> FlushQueue();
    void ProcessCommand();

    /* Command handlers */
    void HandleCreateDebugModeHost(sptr<ICommand> p_command);

    /* function used in command handlers */
    sptr<GameHost> CreateHost();
};
