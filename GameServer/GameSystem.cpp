#include "pch.h"

#include "GameSystem.h"
#include "GameHost.h"
#include "DataSystem.h"

DWORD intervalTick = 1000; // 3초에 한 번씩

namespace
{
#define TO_LAMBDA(FUNC) [&](sptr<ICommand> command) { FUNC(command); }
} // namespace

using namespace Command::M2G;
using namespace Command::N2G;

GameSystem::GameSystem(sptr<DataSystem> p_dataSystem) : dataSystem(p_dataSystem)
{
    // commandHandler.emplace((int)N2G::CommandId::CREATE_DEBUG_MODE_HOST, TO_LAMBDA(HandleCreateDebugModeHost));
}

void GameSystem::Run()
{
    DWORD intervalTick = 20; // 50 frame
    DWORD startTime = 0;
    DWORD nextTickTime = GetTickCount() + intervalTick;
    DWORD deltaTime = 0;
    DWORD prevTime = 0;

    while (true)
    {
        DWORD currentTime = GetTickCount();
        if (startTime == 0)
        {
            startTime = currentTime;
        }

        DWORD elapsedMils = currentTime - startTime;
        DWORD elapsedSec = elapsedMils / 1000;
        if (currentTime > nextTickTime)
        {
            deltaTime = currentTime - prevTime;
            prevTime = currentTime;
            nextTickTime += intervalTick;
            float deltaTimeInSec = elapsedMils / 1000;
            Update(deltaTimeInSec);
        }
    }
}

void GameSystem::Update(float deltaTime)
{
    // GameSystem이 처리해야할 패킷 먼저 처리
    ProcessCommand();
    // Host들 업데이트
    /*for (GameHost* gameHost : gameHostList)
    {
            gameHost->Update(deltaTime);
    }*/
}

queue<sptr<ICommand>> GameSystem::FlushQueue()
{
    WRITE_LOCK;
    queue<sptr<ICommand>> copied(commandQueue);
    return copied;
}

void GameSystem::ProcessCommand()
{
    queue<sptr<ICommand>> copied = FlushQueue();

    while (!copied.empty())
    {
        sptr<ICommand> command = copied.front();
        int commandId = command->GetCommandId();
        if (commandHandler[commandId])
        {
            commandHandler[commandId](command);
        }
        copied.pop();
    }
}

void GameSystem::PushCommand(sptr<ICommand> command)
{
    WRITE_LOCK;
    commandQueue.push(command);
}

sptr<GameHost> GameSystem::CreateHost()
{
    sptr<GameHost> host = make_shared<GameHost>(dataSystem->champDataFactory);

    // Champ pool init
    vector<ChampData> champData = dataSystem->champDataFactory->GetChampPoolData();

    for (ChampData data : champData)
    {
        for (int i = 0; i < data.amount; i++)
        {
            data.uid = (data.index * 10000) + i;
            int cost = data.cost;

            if (host->champPool.find(cost) != host->champPool.end())
            {
                vector<ChampData> temp;
                temp.push_back(data);
                host->champPool.emplace(cost, temp);
            }
            else
            {
                vector<ChampData>& temp = host->champPool[cost];
                temp.push_back(data);
            }
        }
    }

    return host;
}

void GameSystem::HandleCreateDebugModeHost(sptr<ICommand> p_command)
{
    // sptr<CreateDebugModeHostCommand> command = dynamic_pointer_cast<CreateDebugModeHostCommand>(p_command);

    // sptr<GameHost> host = CreateHost();
    // sptr<ClientSession> client = command->client.lock();
    // if (client == nullptr)
    //{
    //     // client deleted
    //     return;
    // }

    // host->EnterClient(client);
    // client->GetPlayer()->currentGame = host;

    // host->Start();

    // gameHostMap.emplace(hostId++, host);
}
