#include "pch.h"
#include "PlayerManager.h"
#include "Player.h"

void PlayerManager::AddPlayer(sptr<ClientSession> client)
{
    WRITE_LOCK;
    client->GetPlayer()->playerId = tempPlayerId;
    clientMap->emplace(tempPlayerId, client);
    tempPlayerId++;
    return;
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