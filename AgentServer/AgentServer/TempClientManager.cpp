#include "pch.h"
#include "TempClientManager.h"
#include "Player.h"

void TempClientManager::AddClient(sptr<ClientSession> client)
{
    WRITE_LOCK;
    int proxyId = tempProxyId;
    clientMap->emplace(proxyId, client);
    tempProxyId++;
    return;
}

void TempClientManager::RemoveClient(int playerId) { clientMap->erase(playerId); }

void TempClientManager::Update()
{
    /*Vector<PlayerRef> copiedPlayers;
    {
            WRITE_LOCK;
            for (auto const& [accountId, player] : *_players) {
                    copiedPlayers.push_back(player);
            }
    }

    for (auto& player : copiedPlayers) {
            player->Update();
    }*/
}

TempClientManager::TempClientManager()
{
    /*auto job = MakeShared<Job>([this]() {
            this->Update();
    });
    Scheduler::SetInterval(job);*/
}