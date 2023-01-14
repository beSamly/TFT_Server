#include "pch.h"
#include "PlayerManager.h"
#include "Player.h"

void PlayerManager::AddPlayer(sptr<ClientSession> client)
{
    WRITE_LOCK;
    clientMap->emplace(tempPlayerId, client);
    tempPlayerId++;
    return;
}

sptr<ClientSession> PlayerManager::FindPlayer(int playerId)
{
    WRITE_LOCK;
    map<int, sptr<ClientSession>>::iterator iter = clientMap->find(playerId);
    return iter == clientMap->end() ? nullptr : iter->second;
}

void PlayerManager::RemovePlayer(int playerId) { clientMap->erase(playerId); }

void PlayerManager::Update()
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

PlayerManager::PlayerManager()
{
    /*auto job = MakeShared<Job>([this]() {
            this->Update();
    });
    Scheduler::SetInterval(job);*/
}