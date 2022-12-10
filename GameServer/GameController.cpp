#include "pch.h"

#include "GameController.h"
#include "GameSystem.h"
#include "PacketId.h"
#include "PacketHeader.h"
#include "spdlog/spdlog.h"

GameController::GameController()
{
    // handlers[(int)PacketId::InGame::BUY] = [&](sptr<ClientSession>& client, BYTE* buffer, int32 len) {
    // this->HandleBuy(client, buffer, len); };
    handlers[(int)PacketId::InGame::BUY] = TO_LAMBDA(HandleBuy);
};

void GameController::HandlePacket(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
    auto packetId = header->id;

    if (handlers[packetId])
    {
        handlers[packetId](session, buffer, len);
    }
    else
    {
        spdlog::error("[GameController] invalid packetId = {}", packetId);
    }
}

void GameController::HandleBuy(sptr<ClientSession>& session, BYTE* buffer, int32 len)
{
    if (sptr<GameHost> gameHost = session->GetPlayer()->currentGame.lock())
    {
        // gameHost->PushCommand(...)
    }

    /* sptr<ICommand> command = make_shared<BuyCommand>(1, 1);
     session->GetPlayer()->currentGame->PushCommand(command);

     gameSystem->PushCommand(1, command);*/
}
