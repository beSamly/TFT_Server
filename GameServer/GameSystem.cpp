#include "pch.h"

#include "GameSystem.h"
#include "GameHost.h"
#include "DataSystem.h"
#include "Command.h"
#include "ProxyManager.h"
#include "PacketId_MT_GM.h"
#include "Packet.h"
#include "HostCreateResponse.pb.h"

DWORD intervalTick = 1000; // 3�ʿ� �� ����

namespace
{
#define TO_LAMBDA(FUNC) [&](sptr<ICommand> command) { FUNC(command); }
} // namespace

using namespace Command::N2G;

GameSystem::GameSystem(sptr<DataSystem> p_dataSystem) : dataSystem(p_dataSystem)
{
    commandHandler.emplace((int)N2G::CommandId::CREATE_HOST, TO_LAMBDA(HandleHostCreate));
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
    // GameSystem�� ó���ؾ��� ��Ŷ ���� ó��
    ProcessCommand();
    // Host�� ������Ʈ
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

sptr<GameHost> GameSystem::GetGameHostForPlayer(int playerId)
{
    if (!mapPlayerIdToMatchId.count(playerId))
    {
        return nullptr;
    }

    int matchId = mapPlayerIdToMatchId[playerId];
    if (!gameHostMap.count(matchId))
    {
        return nullptr;
    }

    return gameHostMap[matchId];
}

void GameSystem::HandleHostCreate(sptr<ICommand> command)
{
    sptr<HostCreateCommand> hostCreateCommand = dynamic_pointer_cast<HostCreateCommand>(command);

    if (!hostCreateCommand)
    {
        return;
    }

    int matchId = hostCreateCommand->matchId;
    vector<int>& vecPlayerId = hostCreateCommand->vecPlayerId;

    sptr<GameHost> host = make_shared<GameHost>(dataSystem->champDataFactory, matchId, vecPlayerId);

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

    gameHostMap.emplace(matchId, host);

    for (int i : vecPlayerId)
    {
        mapPlayerIdToMatchId[i] = matchId;
    }

    // ��û ���� ��ġ ������ ����
    if (sptr<Proxy> proxy = hostCreateCommand->proxy.lock())
    {
        Protocol::HostCreateResponse res;
        res.set_result(true);
        res.set_matchid(matchId);
        // TODO ���߿� ���� �ּ� ��Ʈ
        res.set_address("127.0.0.1");
        res.set_port(5000);

        Packet packet((int)PacketId_MT_GM::Prefix::HOST, (int)PacketId_MT_GM::Host::HOST_CREATE_REQ);
        packet.WriteData<Protocol::HostCreateResponse>(res);
        proxy->Send(packet.GetSendBuffer());
    }
}